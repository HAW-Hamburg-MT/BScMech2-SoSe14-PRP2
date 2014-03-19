/*
 * file: main.c
 * project: BScMech2-SoSe14-PRP2
 * version: 0.9 (19.03.2014 18:00)
 * - 0.9 first Version (not tested with real machine)
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

//#include "cbw.h"
#include "mycbw.h"
#include "functions.h"


int main()
{
    initializeSystem();
    resetOutputs();
    
    while (1) {
        
        changeSensors(); // for debugging without real system
        
        //updateProcessImage();
        updateProcessImage2();
        
        if (isBitSet(ESTOP))
            resetOutputs();
        if (isBitSet(RESET))
            resetOutputs();

        // EVERYTHING ELSE
        
        if (isBitSet(START)) { // TODO ESTOP IS NC !!! NOT NO
            setBitInOutput(MOTOR_R);
            setBitInOutput(LED_Q1);
            setBitInOutput(LIGHT_GN);
        }
        if (isBitSet(STOP)) { // STOP IS NC !!! NOT NO
            clearBitInOutput(MOTOR_R);
            clearBitInOutput(LED_Q1);
            clearBitInOutput(LIGHT_GN);
            setBitInOutput(LIGHT_YE);
        }
        
        // EVERYTHING ELSE END
        
        applyProcessToOutput();
    }
    
    return 0;
}

