/*
 * file: stateMachine.c
 * project: BScMech2-SoSe14-PRP2
 * version: 2.1 (13.05.2014 13:30)
 * - 0.1 first version
 * - 0.2 first and bugs fixed
 * - 0.3 initial logic enhanced, main must not initialize currentState
 * - 1.0 tested and OK, state logic enhancements
 * - 2.0 rewritten for PRP2-A3
 * - 2.1 changes for listDatabase v1.0 + minor bug-fixes
 *
 *
 * Created by Jannik Beyerstedt
 * jannik.beyerstedt.de
 * Copyright: all code under creative commons license: CC BY-NC-SA 3.0
 *
 *
 * HAW Hamburg - Labor Programmieren 2
 * festo conveyor belt system - exercise 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stateMachine.h"
#include "festoFunctions.h"
#include "listDatabase.h"


States currentState = INIT;
States savedState = INIT;

time_t junctionOpenTime = 0;
double junctionOpenDelay = 10; // seconds


void theMachine() {
    
    list_t itemsList = NULL;
    
    listDataPtr dataStore = NULL;
    
    
    switch (currentState) {
        case START:
            if (isTriggered(BTN_ESTOP, 0)) {
                savedState = currentState;
                saveActors();
                resetOutputs();
                printf("theMachine: switched to E_STOP\n");
                
                currentState = E_STOP;
                printf("new: E_STOP\n");
            }else if (hasTriggered(BTN_START)) {
                clearBitInOutput(LED_START);
                setBitInOutput(LIGHT_GN);
                
                if (itemsList == NULL) {
                    itemsList = initializeList();
                }else {
                    deleteList(itemsList);
                    itemsList = initializeList();
                }
                
                currentState = ACTIVE;
                printf("new: ACTIVE\n");
            }
            break;
            
        case ACTIVE:
            if (isTriggered(BTN_ESTOP, 0)) {
                savedState = currentState;
                saveActors();
                resetOutputs();
                printf("theMachine: switched to E_STOP\n");
                
                currentState = E_STOP;
                printf("new: E_STOP\n");
            }else if (hasTriggered(BTN_START)) {               
                clearBitInOutput(ALL_VALUES);
                setBitInOutput(LED_START);
                
                currentState = START;
                printf("new: START\n");
            }else if (isTriggered(POS_IN, 0) && (isTriggered(SNS_SLIDE, 1)) ) {
                addNodeAtEnd(itemsList);
                dataStore = malloc(sizeof(struct listData));
                time(&dataStore->inputTime);
                
                clearBitInOutput(LIGHT_GN);
                setBitInOutput(LIGHT_YE | MOTOR_R);
                
                currentState = TRANSP;
                printf("new: TRANSP\n");
            }else if (isTriggered(POS_IN, 0) && (isTriggered(SNS_SLIDE, 0)) ) {
                printf("+++++ ATTENTION: SLIDE IS FULL +++++\n");
                
            }else;
            break;
            
        case TRANSP:
            if (isTriggered(BTN_ESTOP, 0)) {
                savedState = currentState;
                saveActors();
                resetOutputs();
                printf("theMachine: switched to E_STOP\n");
                
                currentState = E_STOP;
                printf("new: E_STOP\n");
            }else if (hasTriggered(POS_HEIGHT)) {
                clearBitInOutput(MOTOR_R | LIGHT_YE);
                setBitInOutput(LIGHT_RD);
                
                currentState = TRANSP_H;
                printf("new: TRANSP_H\n");
            }else;
            break;
            
        case TRANSP_H:
            if (isTriggered(BTN_ESTOP, 0)) {
                savedState = currentState;
                saveActors();
                resetOutputs();
                printf("theMachine: switched to E_STOP\n");
                
                currentState = E_STOP;
                printf("new: E_STOP\n");
            }else if (isTriggered(SNS_HEIGHT, 0)) { // height OK
                dataStore->height = TRUE;
                
                clearBitInOutput(LIGHT_RD);
                setBitInOutput(MOTOR_R | MOTOR_SLOW | LIGHT_GN | LED_Q1);
                printf("++INFO: Height OK ++\n");
                
                currentState = TRANSP_H1;
                printf("new: TRANSP_H1\n");
            }else if (isTriggered(SNS_HEIGHT, 1)) { // height not OK
                dataStore->height = FALSE;
                
                setBitInOutput(MOTOR_R | MOTOR_SLOW | LIGHT_RD);
                printf("++INFO: Height not OK ++\n");
                
                currentState = TRANSP_H0;
                printf("new: TRANSP_H0\n");
            }else;
            break;
            
        case TRANSP_H0:
            if (isTriggered(BTN_ESTOP, 0)) {
                savedState = currentState;
                saveActors();
                resetOutputs();
                printf("theMachine: switched to E_STOP\n");
                
                currentState = E_STOP;
                printf("new: E_STOP\n");
            }else if (hasTriggered(POS_JUNCT)) {
                clearBitInOutput(LIGHT_GN | MOTOR_R | MOTOR_SLOW);
                setBitInOutput(LIGHT_RD);
                
                currentState = TRANSP_J;
                printf("new: TRANSP_J\n");
            }else;
            break;
            
        case TRANSP_H1:
            if (isTriggered(BTN_ESTOP, 0)) {
                savedState = currentState;
                saveActors();
                resetOutputs();
                printf("theMachine: switched to E_STOP\n");
                
                currentState = E_STOP;
                printf("new: E_STOP\n");
            }else if (hasTriggered(POS_JUNCT)) {
                clearBitInOutput(LIGHT_GN | MOTOR_R | MOTOR_SLOW);
                setBitInOutput(LIGHT_RD);
                
                currentState = TRANSP_J;
                printf("new: TRANSP_J\n");
            }else;
            break;
        
        case TRANSP_J:
            if (isTriggered(BTN_ESTOP, 0)) {
                savedState = currentState;
                saveActors();
                resetOutputs();
                printf("theMachine: switched to E_STOP\n");
                
                currentState = E_STOP;
                printf("new: E_STOP\n");
            }else if (isTriggered(SNS_METAL, 1) && isTriggered(SNS_SLIDE, 1)) {
                dataStore->metal = TRUE;
                printf("++INFO: item is METAL++\n");
                
                setBitInOutput(MOTOR_R | LIGHT_YE);
                
                currentState = TRANSP_M1;
                printf("new: TRANSP_M1\n");
            }else if (isTriggered(SNS_METAL, 1) && isTriggered(SNS_SLIDE, 0)) {
                dataStore->metal = TRUE;
                printf("++INFO: item is METAL++\n");
                
                clearBitInOutput(LIGHT_RD);
                setBitInOutput(MOTOR_R | LIGHT_YE | LED_Q2 | JUNCTION);
                time(&junctionOpenTime);
                
                currentState = TRANSP_M0;
                printf("new: TRANSP_M0\n");
                printf("+++++ ATTENTION: SLIDE IS FULL +++++\n");
            }else if (isTriggered(SNS_METAL, 0)) {
                dataStore->metal = FALSE;
                printf("++INFO: item is NOT METAL++\n");
                
                clearBitInOutput(LIGHT_RD);
                setBitInOutput(MOTOR_R | LIGHT_YE | LED_Q2 | JUNCTION);
                time(&junctionOpenTime);
                
                currentState = TRANSP_M0;
                printf("new: TRANSP_M0\n");
            }else;
            break;
        
        case TRANSP_M0:
            if (isTriggered(BTN_ESTOP, 0)) {
                savedState = currentState;
                saveActors();
                resetOutputs();
                printf("theMachine: switched to E_STOP\n");
                
                currentState = E_STOP;
                printf("new: E_STOP\n");
            }else if (hasTriggered(POS_OUT)) {
                time(&dataStore->outputTime);
                dataStore = getNodeData(itemsList, -1); // store data in last Node
                
                clearBitInOutput(MOTOR_R | JUNCTION | LED_Q2 | LIGHT_YE);
                junctionOpenTime = 0;
                setBitInOutput(LIGHT_GN | LED_START);
                
                currentState = AT_END;
                printf("new: AT_END\n");
            }else;
            break;
        
        case TRANSP_M1:
            if (isTriggered(BTN_ESTOP, 0)) {
                savedState = currentState;
                saveActors();
                resetOutputs();
                printf("theMachine: switched to E_STOP\n");
                
                currentState = E_STOP;
                printf("new: E_STOP\n");
            }else if (hasTriggered(SNS_SLIDE)) {
                time(&dataStore->outputTime);
                dataStore = getNodeData(itemsList, -1); // store data in last Node
                
                clearBitInOutput(MOTOR_R | LIGHT_YE);
                setBitInOutput(LED_START);
                
                currentState = AT_SLIDE;
                printf("new: AT_SLIDE\n");
            }else;
            break;
        
        case AT_SLIDE:
            if (isTriggered(BTN_ESTOP, 0)) {
                savedState = currentState;
                saveActors();
                resetOutputs();
                printf("theMachine: switched to E_STOP\n");
                
                currentState = E_STOP;
                printf("new: E_STOP\n");
            }else if (hasTriggered(BTN_START)) {
                outputList(itemsList);
                
                clearBitInOutput(ALL_VALUES);
                setBitInOutput(LED_START);
                
                currentState = START;
                printf("new: START\n");
            }else if (isTriggered(POS_IN, 0) && (isTriggered(SNS_SLIDE, 1)) ) {
                addNodeAtEnd(itemsList);
                dataStore = malloc(sizeof(struct listData));
                time(&dataStore->inputTime);
                
                clearBitInOutput(LIGHT_GN);
                setBitInOutput(LIGHT_YE | MOTOR_R);
                
                currentState = TRANSP;
                printf("new: TRANSP\n");
            }else if (isTriggered(POS_IN, 0) && (isTriggered(SNS_SLIDE, 0)) ) {
                printf("+++++ ATTENTION: SLIDE IS FULL +++++\n");
            }else;
            break;
            
        case AT_END:
            if (isTriggered(BTN_ESTOP, 0)) {
                savedState = currentState;
                saveActors();
                resetOutputs();
                printf("theMachine: switched to E_STOP\n");
                
                currentState = E_STOP;
                printf("new: E_STOP\n");
            }else if (hasTriggered(BTN_START)) {
                clearBitInOutput(ALL_VALUES);
                setBitInOutput(LED_START);
                
                currentState = START;
                printf("new: START\n");
            }else if (isTriggered(POS_IN, 0) && isTriggered(POS_OUT, 1) && (isTriggered(SNS_SLIDE, 1)) ) {
                addNodeAtEnd(itemsList);
                dataStore = malloc(sizeof(struct listData));
                time(&dataStore->inputTime);
                
                clearBitInOutput(LIGHT_GN);
                setBitInOutput(LIGHT_YE | MOTOR_R);
                
                currentState = TRANSP;
                printf("new: TRANSP\n");
            }else if (isTriggered(POS_IN, 0) && isTriggered(POS_OUT, 0) ) {
                printf("+++++ ATTENTION: PLEASE REMOVE ITEM AT END +++++\n");
            }else;
            break;
            
        case E_STOP:
            if (isTriggered(BTN_ESTOP, 1)) {
                restoreActors();
                currentState = savedState;
            }else;
            break;
        
        case INIT:
            currentState = START;
            
        default:                
            clearBitInOutput(ALL_VALUES);
            setBitInOutput(LED_START);
            currentState = START;
            printf("ERROR: theMachine: invalid state -> reset to start\n");
            break;
    }
    
    
    // force close junction if open for too long time
    if ( (difftime(time(NULL), junctionOpenTime) > junctionOpenDelay ) && (junctionOpenTime != 0) ) {
        clearBitInOutput(JUNCTION | LED_Q2);
        junctionOpenTime = 0;
        printf("ATTENTION: theMachine: junction closed because too long open\n");
    }
    
    
}