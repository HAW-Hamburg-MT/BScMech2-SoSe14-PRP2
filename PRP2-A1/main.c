/*
 * file: main.c
 * project: BScMech2-SoSe14-PRP2
 * version: 1.0 (01.04.2014 18:00)
 * - 0.9 first Version (not tested with real machine)
 * - 1.0 stable and tested
 * 
 *
 * Created by Jannik Beyerstedt
 * jannik.beyerstedt.de
 * Copyright: all code under creative commons licence: CC BY-NC-SA 3.0
 *
 *
 * HAW Hamburg - Labor Programmieren 2
 * festo conveyor belt system - excercise 1
 */

#include <stdio.h>
#include "functions.h"

//#include "mycbw.h"  // ONLY FOR TESTING


void excercise (int *exitVariable) {
    
    char option;
    printf("choose option (a - l) :");
    fflush(stdin);
    scanf("%c", &option);
    
    switch (option) {
        case ('a'):
            clearBitInOutput(0x0fff);
            setBitInOutput(MOTOR_L);
            break;
        case ('b'):
            clearBitInOutput(0x0fff);
            setBitInOutput(MOTOR_R | MOTOR_SLOW | LIGHT_RD);
            break;
        case ('c'):
            clearBitInOutput(0x0fff);
            setBitInOutput(MOTOR_R | MOTOR_SLOW | LIGHT_YE | JUNCTION);
            break;
        case ('d'):
            clearBitInOutput(0x0fff);
            setBitInOutput(MOTOR_STOP);
            break;
        case ('e'):
            if(isBitNotSet(POS_IN))
                printf("Werkstueck im Einlauf\n");
            break;
        case ('f'):
            if(isBitNotSet(POS_HEIGHT))
                printf("Werkstueck in Hoehenmessung\n");
            break;
        case ('g'):
            if(isBitNotSet(POS_JUNCT) && isBitSet(METAL_ST))
                printf("Werkstueck im Weiche und Metall\n");
            break;
        case ('h'):
            if(isBitNotSet(SLIDE_ST))
                printf("Rutsche voll\n");
            break;
        case ('i'):
            if(isBitNotSet(STOP))
                printf("STOP gedrueckt\n");
            break;
        case ('j'):
            if(isBitSet(RESET))
                printf("RESET gedrueckt\n");
            break;
        case ('k'):
            if(isBitNotSet(ESTOP))
                printf("NOT-AUS gedrueckt\n");
            break;
        case ('l'):
            clearBitInOutput(0x0fff);
            setBitInOutput(LED_Q2 | LED_START);
            break;
        case ('m'):
            clearBitInOutput(0x0fff);
            break;
        case ('x'):
            *exitVariable = 0;
            break;
    }
    
}



int main()
{
    initializeSystem();
    resetOutputs();
    updateProcessImage(); // set inital sensor Values
    
    int inputOptionsExit = 1;
    
    while (1) {
        //changeSensors(); // for debugging without real system
        
        updateProcessImage();
        
        if (isBitNotSet(ESTOP)) { // Emergency funcitons
            resetOutputs();
        } else {
            
            if (inputOptionsExit) { // something to exit the excercise input promts
                excercise(&inputOptionsExit); // do the excercise
            }
            
            // Something to play with
            if (isBitSet(RESET)) {
                resetOutputs();
            }
            if (isBitSet(START)) {
                clearBitInOutput(0x0fff);
                setBitInOutput(MOTOR_R | LED_Q1 | LIGHT_GN);
            }
            if (isBitNotSet(STOP)) {
                clearBitInOutput(0x0fff);
                setBitInOutput(LIGHT_YE);
            }
            // END something to play with
        }
        
        applyProcessToOutput();
    }
    
    return 0;
}

