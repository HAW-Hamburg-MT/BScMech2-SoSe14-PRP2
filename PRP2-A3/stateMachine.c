/*
 * file: stateMachine.c
 * project: BScMech2-SoSe14-PRP2
 * version: 2.0 (01.05.2014 12:30)
 * - 0.1 first version
 * - 0.2 first and bugs fixed
 * - 0.3 initial logic enahnced, main must not initialize currentState
 * - 1.0 tested and OK, state logic enhancements
 * - 2.0 rewritten for PRP2-A3
 *
 *
 * Created by Jannik Beyerstedt
 * jannik.beyerstedt.de
 * Copyright: all code under creative commons license: CC BY-NC-SA 3.0
 *
 *
 * HAW Hamburg - Labor Programmieren 3
 * festo conveyor belt system - exercise 3
 */

#include <stdio.h>
#include <time.h>
#include "stateMachine.h"
#include "festoFunctions.h"
#include "listDatabase.h"


States currentState = INIT;
States lastState = INIT;
States savedState = INIT;

time_t junctionOpenTime;
double junctionOpenDelay = 10; // seconds


void theMachine() {
    
    if (currentState == INIT) {
        currentState = START;
    }
    
    time_t inputTime;
    Boolean height;
    Boolean metal;
    time_t outputTime;
    
    
    // do state transition action
    if (currentState != lastState) {
        switch (currentState) {
            case START:
                outputList();
                initializeList();
                
                clearBitInOutput(ALL_VALUES);
                setBitInOutput(LED_START);
                break;
            
            case ACTIVE:
                deleteList();
                initializeList();
                
                clearBitInOutput(LED_START);
                setBitInOutput(LIGHT_GN);
                break;
                
            case TRANSP:
                addNodeAtEnd();
                time(&inputTime);
                addDataToLastNode(1, &inputTime);
                
                clearBitInOutput(LIGHT_GN);
                setBitInOutput(LIGHT_YE | MOTOR_R);
                break;
                
            case TRANSP_H:
                clearBitInOutput(MOTOR_R | LIGHT_YE);
                setBitInOutput(LIGHT_RD);
                break;
                
            case TRANSP_H0:
                height = FALSE;
                addDataToLastNode(2, &height);
                
                setBitInOutput(MOTOR_R | MOTOR_SLOW | LIGHT_RD);
                printf("++ Height not OK ++\n");
                break;
                
            case TRANSP_H1:
                height = TRUE;
                addDataToLastNode(2, &height);
                
                clearBitInOutput(LIGHT_RD);
                setBitInOutput(MOTOR_R | MOTOR_SLOW | LIGHT_GN | LED_Q1);
                printf("++ Height OK ++\n");
                break;
                
            case TRANSP_J:
                clearBitInOutput(LIGHT_GN | MOTOR_R | MOTOR_SLOW);
                setBitInOutput(LIGHT_RD);
                break;
                
            case TRANSP_M0:
                metal = FALSE;
                addDataToLastNode(3, &metal);
                
                clearBitInOutput(LIGHT_RD);
                setBitInOutput(MOTOR_R | LIGHT_YE | LED_Q2 | JUNCTION);
                time(&junctionOpenTime);
                break;
                
            case TRANSP_M1:
                metal = TRUE;
                addDataToLastNode(3, &metal);
                
                setBitInOutput(MOTOR_R | LIGHT_YE);
                break;
                
            case AT_SLIDE:
                time(&outputTime);
                addDataToLastNode(4, &outputTime);
                
                clearBitInOutput(MOTOR_R | LIGHT_YE);
                setBitInOutput(LED_START);
                break;
                
            case AT_END:
                time(&outputTime);
                addDataToLastNode(4, &outputTime);
                
                clearBitInOutput(MOTOR_R | JUNCTION | LED_Q2 | LIGHT_YE);
                setBitInOutput(LIGHT_GN | LED_START);
                break;
            
            case E_STOP:
                savedState = lastState;
                saveActors();
                printf("theMachine: switched to E_STOP\n");
                break;
                
            default:
                printf("ERROR: theMachine: invalid state transition");
                break;
        }
        
    }else; // END state transition action
    
    
    lastState = currentState;
    
    
    // do action in state (read sensors and switch state)
    switch (currentState) {
        case START:
            if (isTriggered(BTN_ESTOP, 0)) {
                currentState = E_STOP;
                printf("new: E_STOP\n");
            }else if (hasTriggered(BTN_START)) {
                currentState = ACTIVE;
                printf("new: ACTIVE\n");
            }
            break;
            
        case ACTIVE:
            if (isTriggered(BTN_ESTOP, 0)) {
                currentState = E_STOP;
                printf("new: E_STOP\n");
            }else if (hasTriggered(BTN_START)) {
                currentState = START;
                printf("new: START\n");
            }else if (isTriggered(POS_IN, 0)) {
                currentState = TRANSP;
                printf("new: TRANSP\n");
            }else;
            break;
            
        case TRANSP:
            if (isTriggered(BTN_ESTOP, 0)) {
                currentState = E_STOP;
                printf("new: E_STOP\n");
            }else if (hasTriggered(POS_HEIGHT)) {
                currentState = TRANSP_H;
                printf("new: TRANSP_H\n");
            }else;
            break;
            
        case TRANSP_H:
            if (isTriggered(BTN_ESTOP, 0)) {
                currentState = E_STOP;
                printf("new: E_STOP\n");
            }else if (isTriggered(SNS_HEIGHT, 1)) { // height OK
                currentState = TRANSP_H1;
                printf("new: TRANSP_H1\n");
            }else if (isTriggered(SNS_HEIGHT, 0)) { // height not OK
                currentState = TRANSP_H0;
                printf("new: TRANSP_H0\n");
            }else;
            break;
            
        case TRANSP_H0:
            if (isTriggered(BTN_ESTOP, 0)) {
                currentState = E_STOP;
                printf("new: E_STOP\n");
            }else if (hasTriggered(POS_JUNCT)) {
                currentState = TRANSP_J;
                printf("new: TRANSP_J\n");
            }else;
            break;
            
        case TRANSP_H1:
            if (isTriggered(BTN_ESTOP, 0)) {
                currentState = E_STOP;
                printf("new: E_STOP\n");
            }else if (hasTriggered(POS_JUNCT)) {
                currentState = TRANSP_J;
                printf("new: TRANSP_J\n");
            }else;
            break;
        
        case TRANSP_J:
            if (isTriggered(BTN_ESTOP, 0)) {
                currentState = E_STOP;
                printf("new: E_STOP\n");
            }else if (isTriggered(SNS_METAL, 1) && isTriggered(SNS_SLIDE, 1)) {
                currentState = TRANSP_M1;
                printf("new: TRANSP_M1\n");
            }else if (isTriggered(SNS_METAL, 1) && isTriggered(SNS_SLIDE, 0)) {
                currentState = TRANSP_M0;
                printf("new: TRANSP_M0\n");
                printf("+++++ ATTENTION: SLIDE IS FULL +++++");
            }else if (isTriggered(SNS_METAL, 0)) {
                currentState = TRANSP_M0;
                printf("new: TRANSP_M0\n");
            }else;
            break;
        
        case TRANSP_M0:
            if (isTriggered(BTN_ESTOP, 0)) {
                currentState = E_STOP;
                printf("new: E_STOP\n");
            }else if (hasTriggered(SNS_SLIDE)) {
                currentState = AT_SLIDE;
                printf("new: AT_SLIDE\n");
            }else;
            break;
        
        case TRANSP_M1:
            if (isTriggered(BTN_ESTOP, 0)) {
                currentState = E_STOP;
                printf("new: E_STOP\n");
            }else if (hasTriggered(POS_OUT)) {
                currentState = AT_END;
                printf("new: AT_END\n");
            }else;
            break;
        
        case AT_SLIDE:
            if (isTriggered(BTN_ESTOP, 0)) {
                currentState = E_STOP;
                printf("new: E_STOP\n");
            }else if (hasTriggered(BTN_START)) {
                currentState = START;
                printf("new: START\n");
            }else if (isTriggered(POS_IN, 0)) {
                currentState = TRANSP;
                printf("new: TRANSP\n");
            }else;
            break;
            
        case AT_END:
            if (isTriggered(BTN_ESTOP, 0)) {
                currentState = E_STOP;
                printf("new: E_STOP\n");
            }else if (hasTriggered(BTN_START)) {
                currentState = START;
                printf("new: START\n");
            }else if (isTriggered(POS_IN, 0) && isTriggered(POS_OUT, 1)) {
                currentState = TRANSP;
                printf("new: TRANSP\n");
            }else if (isTriggered(POS_IN, 0) && isTriggered(POS_OUT, 0)) {
                printf("+++++ ATTENTION: PLEASE REMOVE ITEM AT END +++++\n");
            }else;
            break;
            
        case E_STOP:
            if (isTriggered(BTN_ESTOP, 0)) {
                currentState = E_STOP;
                printf("new: E_STOP\n");
            }else if (isTriggered(BTN_ESTOP, 1)) {
                restoreActors();
                currentState = savedState;
            }else;
            break;
            
        default:
            currentState = START;
            lastState = INIT;
            printf("ERROR: theMachine: invalid state -> reset to start\n");
            break;
    }// END switch state sensor read action
    
    
    // force close junction if open for too long time
    if ( difftime(junctionOpenTime, time(NULL)) > junctionOpenDelay ) {
        clearBitInOutput(JUNCTION | LED_Q2);
        printf("ATTENTION: theMachine: junction closed because too long open");
    }
    
    
}