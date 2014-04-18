/*
 * file: main.c
 * project: BScMech2-SoSe14-PRP2
 * version: 0.2 (14.04.2014 10:00)
 * - 0.2 changes for v0.3 of stateMachine
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
#include <stdlib.h>

#include "systemFunctions.h"
#include "stateMachine.h"

//#include "mycbw.h"  // ONLY FOR TESTING


int main() {
    initializeSystem();
    resetOutputs();
    updateProcessImage(); // set inital sensor Values
    
    States machineStates;
    
    while (1) {
        //changeSensors(); // for debugging without real system
        
        updateProcessImage();
        
        // Emergency function
        if (isTriggered(BTN_ESTOP, 0)) {
            resetOutputs();
        } else {
            // !-- code for normal execution HERE --!
            
            theMachine(&machineStates);
            
        }// END EMERGENCY
        
        applyProcessToOutput();
    }
    return (EXIT_SUCCESS);
}

