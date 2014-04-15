/*
 * file: main.c
 * project: BScMech2-SoSe14-PRP2
 * version: 0.1 (14.04.2014 10:00)
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
        if (isBitNotSet(BTN_ESTOP)) {
            resetOutputs();
        } else {
            // code for normal execution HERE
            
            theMachine(&machineStates);
            
        }// END EMERGENCY
        
        applyProcessToOutput();
    }
    return (EXIT_SUCCESS);
}

