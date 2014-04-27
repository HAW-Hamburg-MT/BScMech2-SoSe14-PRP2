/*
 * file: main.c
 * project: BScMech2-SoSe14-PRP2
 * version: 0.1 (27.04.2014 14:30)
 * - 0.1 first version
 *
 *
 * Created by Jannik Beyerstedt
 * jannik.beyerstedt.de
 * Copyright: all code under creative commons licence: CC BY-NC-SA 3.0
 *
 *
 * HAW Hamburg - Labor Programmieren 3
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
        
        // Emergency function
        if (isTriggered(BTN_ESTOP, 0)) {
            resetOutputs();
        } else {
            // !-- code for normal execution HERE --!
            
            theMachine();
            
        }// END EMERGENCY
        
        applyProcessToOutput();
    }
    return (EXIT_SUCCESS);
}

