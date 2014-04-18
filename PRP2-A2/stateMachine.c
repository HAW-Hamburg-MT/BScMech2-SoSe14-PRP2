/*
 * file: stateMachine.c
 * project: BScMech2-SoSe14-PRP2
 * version: 0.3 (18.04.2014 11:30)
 * - 0.1 first version
 * - 0.2 first and bugs fixed
 * - 0.3 inital logic enahnced, main must not initialize currentState
 *
 *
 * Created by Jannik Beyerstedt
 * jannik.beyerstedt.de
 * Copyright: all code under creative commons licence: CC BY-NC-SA 3.0
 *
 *
 * HAW Hamburg - Labor Programmieren 2
 * festo conveyor belt system - excercise 2
 */

#include <stdio.h>
#include "stateMachine.h"
#include "systemFunctions.h"

void theMachine(States *currentState) {
    
    switch (*currentState) {
        case START: // initial state
            /*
             + traffic lights off
             + LED_START on
             -> ACTIVE at BTN_START
            */
            
            setOutput(LED_START);
            
            if (hasTriggered(BTN_START)) {
                *currentState = ACTIVE;
                printf("new: ACTIVE\n");
            }else;
            
            break;
        case ACTIVE:  // active state
            /*
             + traffic lights green
             -> TRANSP at POS_IN
             -> START  at BTN_START
             */
            
            setOutput(LIGHT_GN);
            
            if (hasTriggered(POS_IN)) {
                *currentState = TRANSP;
                printf("new: TRANSP\n");
            } else if (hasTriggered(BTN_START)) {
                *currentState = START;
                printf("new: START\n");
            } else;
    
            break;
        case TRANSP:  // transport state
            /*
             + transport (fast) right
             + traffic lights green to yellow
             -> TRANSP_H at POS_HEIGHT
             */
            
            //setOutput(LIGHT_GN | MOTOR_R);
            
            clearBitInOutput(RST_MOTOR | RST_LIGHT);
            setBitInOutput(LIGHT_YE);
            setBitInOutput(MOTOR_R);
            
            if (hasTriggered(POS_HEIGHT)) {
                *currentState = TRANSP_H;
                printf("new: TRANSP_H\n");
            }
            
            break;
        case TRANSP_H: // transport at height sensor
            /*
             + stop transporting
             + traffic lights yellow to red
             -> TRANSP_H1 at height in range
             -> TRANSP_H0 at height not in range
             */
            
            clearBitInOutput(RST_MOTOR | RST_LIGHT);
            setBitInOutput(LIGHT_RD);
            
            if (isTriggered(SNS_HEIGHT, 0)) {
                *currentState = TRANSP_H1;
                printf("height OK");
                printf("new: TRANSP_H1\n");
            }else if (isTriggered(SNS_HEIGHT, 1)) {
                *currentState = TRANSP_H0;
                printf("height not OK");
                printf("new: TRANSP_H0\n");
            }else;
            
            break;
        case TRANSP_H1: // transport if height in range
            /*
             + transport slowly right
             + traffic lights green
             + Q1 until new item at POS_IN
             -> TRANSP_J at POS_JUNCT
             */
            
            clearBitInOutput(RST_MOTOR | RST_LIGHT);
            setBitInOutput(MOTOR_R | MOTOR_SLOW);
            setBitInOutput(LED_Q1 | LIGHT_GN);
            
            if (hasTriggered(POS_JUNCT)) {
                *currentState = TRANSP_J;
                printf("new: TRANSP_J\n");
            }
            
            break;
        case TRANSP_H0: // transport if height NOT in range
            /*
             + transport slowly right
             + traffic lights red
             + Q1 off (no change)
             -> TRANSP_J at POS_JUNCT
             */
            
            clearBitInOutput(RST_MOTOR | RST_LIGHT);
            setBitInOutput(MOTOR_R | MOTOR_SLOW);
            setBitInOutput(LIGHT_RD);
            
            if (hasTriggered(POS_JUNCT)) {
                *currentState = TRANSP_J;
                printf("new: TRANSP_J\n");
            }
            
            break;
        case TRANSP_J:  // transport at junction
            /*
             + stop transporting
             + traffic lights red
             -> TRANSP_M0 at no metal
             -> TRANSP_M1 at is metal
             */
            
            clearBitInOutput(RST_MOTOR | RST_LIGHT);
            setBitInOutput(LIGHT_RD);
            
            if (isTriggered(SNS_METAL, 1)) {
                *currentState = TRANSP_M1;
                printf("new: TRANSP_M1\n");
            }else if (isTriggered(SNS_METAL, 0)){
                *currentState = TRANSP_M0;
                printf("new: TRANSP_M0\n");
            }else;
            
            break;
        case TRANSP_M0: // transport no metal
            /*
             + transport (fast) right
             + traffic lights yellow
             + junction open (on) and Q2 on
             -> AT_SLIDE at SNS_SLIDE
             -> AT_END   at POS_END
             */
            
            setBitInOutput(MOTOR_R);
            setBitInOutput(JUNCTION | LED_Q2);
            setBitInOutput(LIGHT_YE);
            
            if (hasTriggered(SNS_SLIDE)) {
                *currentState = AT_SLIDE;
                printf("new: AT_SLIDE\n");
            }else if (hasTriggered(POS_OUT)) {
                *currentState = AT_END;
                printf("new: AT_END\n");
            }else;
            
            break;
        case TRANSP_M1: // transport metal
            /*
             + transport (fast) right
             + traffic lights yellow and red
             + junction keeps closed and Q2 keeps off
             -> AT_SLIDE at SNS_SLIDE
             -> AT_END   at POS_END
             */
            
            setBitInOutput(MOTOR_R);
            setBitInOutput(LIGHT_YE | LIGHT_RD);
            
            if (hasTriggered(SNS_SLIDE)) {
                *currentState = AT_SLIDE;
                printf("new: AT_SLIDE\n");
            }else if (hasTriggered(POS_OUT)) {
                *currentState = AT_END;
                printf("new: AT_END\n");
            }else;
            
            break;
        case AT_SLIDE:  // end state for metal items
            /*
             + stop transporting
             + traffic lights red
             + turn junction off and Q2 off (keeps state)
             -> TRANSP at POS_IN
             -> START  at BTN_STOP
             */
            
            // TODO ACTIVE ONLY IF NO ITEM AT END
            
            clearBitInOutput(RST_MOTOR | RST_LIGHT);
            setBitInOutput(MOTOR_STOP);
            setBitInOutput(LIGHT_RD);
            clearBitInOutput(JUNCTION | LED_Q2);
            
            if (hasTriggered(BTN_STOP)) {
                *currentState = START;
                printf("new: START\n");
            }else if (hasTriggered(POS_IN)) {
                *currentState = TRANSP;
                printf("new: TRANSP\n");
            }else if (hasTriggered(BTN_START)) {
                *currentState = ACTIVE;
                printf("new: ACTIVE\n");
            }
            
            break;
        case AT_END:   // end state for non metal items
            /*
             + stop transporting
             + traffic lights green
             + turn junction off and Q2 off
             -> TRANSP at POS_IN
             -> START  at BTN_STOP
             */
            
            // TODO ACTIVE ONLY IF NO ITEM AT END
            
            clearBitInOutput(RST_MOTOR | RST_LIGHT);
            setBitInOutput(MOTOR_STOP);
            setBitInOutput(LIGHT_GN);
            clearBitInOutput(JUNCTION | LED_Q2);
            
            if (hasTriggered(BTN_STOP)) {
                *currentState = START;
                printf("new: START\n");
            }else if (hasTriggered(POS_IN)) {
                *currentState = TRANSP;
                printf("new: TRANSP\n");
            }else if (hasTriggered(BTN_START)) {
                *currentState = ACTIVE;
                printf("new: ACTIVE\n");
            }
            
            break;
            
        default:    // INITIALIZE STATE
            *currentState = START;
            break;
            
    }//END SWITCH
    
}