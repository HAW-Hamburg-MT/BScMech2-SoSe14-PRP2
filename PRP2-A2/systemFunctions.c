/*
 * file: systemFunctions.h
 * project: BScMech2-SoSe14-PRP2
 * version: 1.2 (15.04.2014 14:00)
 * - 0.9 first Version (not tested with real machine)
 * - 1.0 stable and tested for PRP2-A1
 * - 1.1 motor safety added
 * - 1.2 new function setOutput added
 * - 1.2.1 several bugfixes and isTriggered enhanced
 *
 *
 * Created by Jannik Beyerstedt
 * jannik.beyerstedt.de
 * Copyright: all code under creative commons licence: CC BY-NC-SA 3.0
 *
 *
 * HAW Hamburg - Labor Programmieren 2
 * festo conveyor belt system - system functions library
 */

#include <stdio.h>
#include "systemFunctions.h"
#include "mycbw.h"  // ONLY FOR TESTING
//#include "cbw.h"


#define TRUE 1
#define FALSE 0


typedef unsigned short int Byte;


Image actorsImage = 0x0000;
Image sensorsImage = 0x0000;
Image changed0to1 = 0x0000;
Image changed1to0 = 0x0000;
Image lastReadingImage = 0x0000;


void initializeSystem() {
    cbDConfigPort(BNR, FIRSTPORTA, DIGITALOUT);
    cbDConfigPort(BNR, FIRSTPORTB, DIGITALIN);
    cbDConfigPort(BNR, FIRSTPORTCL, DIGITALOUT);
    cbDConfigPort(BNR, FIRSTPORTCH, DIGITALIN);
}


void updateProcessImage() { // reads all sensor values AND sorts by 0->1 and 1->0 changes
    Byte reading = 0x00;
    Image changedYes = 0x0000;
    
    cbDIn(BNR, FIRSTPORTB, &reading);
    sensorsImage = reading;
    cbDIn(BNR, FIRSTPORTCH, &reading);
    sensorsImage += (reading << 8);
    
    // 0 to 1
    changedYes = lastReadingImage ^ sensorsImage;
    changed0to1 = changedYes & sensorsImage;
    
    // 1 to 0
    changedYes = lastReadingImage ^ sensorsImage;
    changed1to0 = changedYes & lastReadingImage;
    
    lastReadingImage = sensorsImage;
}

void applyProcessToOutput() { // writes local process image actor states to output ports
    Byte actorOutput = 0x00;
    
    // MOTOR SAFETY, last instance (should be made ok before this step)
    Image bothMotorsSet = actorsImage & (MOTOR_R | MOTOR_L);
    if (bothMotorsSet == (MOTOR_R | MOTOR_L)) {
        clearBitInOutput(MOTOR_R | MOTOR_L);
        printf("ERROR: applyProcessToOutput: Motor L and R are set");
    }
    
    actorOutput = actorsImage;
    cbDOut(BNR, FIRSTPORTA, actorOutput);
    actorOutput = (actorsImage >> 8);
    cbDOut(BNR, FIRSTPORTCL, actorOutput);
}



int hasTriggered (Image mask) {     // NEW: checks whether some sensor has changed it´s state (0->1, 1->0)
    Image maskedBitIsOK = 0x0000;
    
    if ((mask & HAS_TRIG_VALID) == mask) {
        // to filter some sensors which are ONLY interstig for one change type (0->1 or 1->0)
        maskedBitIsOK = ((changed0to1 & SENSORS_NO) | (changed1to0 & SENSORS_NC)) & mask;
        
        if (maskedBitIsOK == mask) {
            return 1;
        }else {
            return 0;
        }
    }
    else {
        printf("ERROR: hasTriggered: invalid mask");
        return -1; // error code
    }
}

int isTriggered (Image mask, int state) {      // NEW: checks whether some sensor has active/ triggered state
    Image maskedBitIsOK = 0x0000;
    int maskIsValid = 0;
    
    if ((mask & IS_TRIG_VALID) == mask) {
        maskIsValid = TRUE;
    }else {
        maskIsValid = FALSE;
        printf("ERROR: isTriggered: invalid mask");
    }
    
    maskedBitIsOK = sensorsImage & mask;
    
    if (maskIsValid && state == 1) {       // check for 1
        if (maskedBitIsOK == mask ) {
            return 1;
        }else {
            return 0;
        }
        
    } else if (maskIsValid && state == 0){ // check for 0
        if (maskedBitIsOK == 0x0000) {
            return 1;
        }else {
            return 0;
        }
        
    } else {
        printf("ERROR: isTriggered: other error");
        return -1;
    }
    
}



void setBitInOutput (Image mask) { // gets bitmask and sets these bits in processimage (actors)
    // --- MOTOR SAFETY ---
    // checks if motor is switched to MOTOR_R at same time as MOTOR_L is enabeled
    if ( ((mask & MOTOR_R) == MOTOR_R) & ((actorsImage & MOTOR_L) == MOTOR_L) ) {
        clearBitInOutput(MOTOR_L);
        applyProcessToOutput();
    }else if ( ((mask & MOTOR_L) == mask) & ((actorsImage & MOTOR_R) == MOTOR_R) ) {
        clearBitInOutput(MOTOR_R);
        applyProcessToOutput();
    }else;
    
    actorsImage = actorsImage | mask;
}

void clearBitInOutput (Image mask) { // gets bitmask and deletes these bits in processimage (actors)
    actorsImage = actorsImage & (~mask);
}

void setOutput (Image mask) {       // sets output to mask
    actorsImage = mask;
}

void resetOutputs () {              // sets all actors to a save value and writes to output ports (e.g. E-Stop)
    actorsImage = E_SAVE;
    
    printf("\n -----RESET FUNCTION TRIGGERED----- \n");
}


int isBitSet (Image mask) {          // DEPRICATED: gets bitmask, checks if these bits are set in process
    Image maskedBitIsOK = 0x0000;
    
    maskedBitIsOK = sensorsImage & mask;
    
    if (maskedBitIsOK == mask)
        return 1;
    else
        return 0;
}

int isBitNotSet (Image mask) {      // DEPRICATED: gets bitmask, checks if all bits are not set process (IS NEEDED)
    Image maskedBitIsOK = 0x0000;
    
    maskedBitIsOK = (sensorsImage ^ mask) & mask;
    
    if (maskedBitIsOK == mask)
        return 1;
    else
        return 0;
}

int hasBitChanged01 (Image mask) {  // DEPRICATED: gets bitmask, checks if all bits changed from 0 to 1
    Image maskedBitIsOK = 0x0000;
    
    maskedBitIsOK = changed0to1 & mask;
    
    if (maskedBitIsOK == mask)
        return 1;
    else
        return 0;
}

int hasBitChanged10 (Image mask) {  // DEPRICATED: gets bitmask, checks if all bits changed from 1 to 0
    Image maskedBitIsOK = 0x0000;
    
    maskedBitIsOK = changed1to0 & mask;
    
    if (maskedBitIsOK == mask)
        return 1;
    else
        return 0;
}