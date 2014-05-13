/*
 * file: main.c
 * project: BScMech2-SoSe14-PRP2
 * version: 1.0 (13.05.2014 13:30)
 * - 0.1 first version
 * - 0.2 updated for emergency stop functions implemented in stateMachine
 * - 1.0 stable and tested (for stateMachine v2.0+)
 *
 *
 * Created by Jannik Beyerstedt
 * jannik.beyerstedt.de
 * Copyright: all code under creative commons licence: CC BY-NC-SA 3.0
 *
 *
 * HAW Hamburg - Labor Programmieren 2
 * festo conveyor belt system - excercise 3
 */

#include <stdio.h>
#include <stdlib.h>

#include "festoFunctions.h"
#include "stateMachine.h"

//#include "mycbw.h"  // ONLY FOR TESTING


int main() {
    initializeSystem();
    resetOutputs();
    updateProcessImage(); // set inital sensor Values
    
    while (1) {
        //changeSensors(); // for debugging without real system
        
        updateProcessImage();
        
        // !-- code for normal execution HERE --!
        theMachine();
        
        
        applyProcessToOutput();
    }
    return (EXIT_SUCCESS);
}

