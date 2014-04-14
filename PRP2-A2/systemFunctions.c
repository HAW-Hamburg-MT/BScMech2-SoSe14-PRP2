/*
 * file: systemFunctions.h
 * project: BScMech2-SoSe14-PRP2
 * version: 1.0 (01.04.2014 18:00)
 * - 0.9 first Version (not tested with real machine)
 * - 1.0 stable and tested for PRP2-A1
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
#include "functions.h"
#include "mycbw.h"  // ONLY FOR TESTING
//#include "cbw.h"


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


void updateProcessImage() { // writes all sensor values to local process image AND sorts by 0->1 and 1->0 changes
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
    if (isBitSet(MOTOR_R | MOTOR_L)) {
        clearBitInOutput(MOTOR_R | MOTOR_L);
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
        
        if (maskedBitIsOK == mask)
            return 1;
        else
            return 0;
    }
    else
        return -1; // error code,
}

int isTriggered (Image mask) {      // NEW: checks whether some sensor has active/ triggered state
    Image maskedBitIsOK = 0x0000;
    
    maskedBitIsOK = sensorsImage & mask;
    
    if ((mask & IS_TRIG_VALID) == mask) {
        if (maskedBitIsOK == mask)  // all tested bits set
            return 1;
        else if (maskedBitIsOK == 0)// all tested bits not set
            return 0;
        else                        // some tested bits are not OK
            return 2;
    }
    else
        return -1; // error
}



void setBitInOutput(Image mask) { // gets bitmask and sets these bits in processimage (actors)
    // --- MOTOR SAFETY ---
    if ( ((mask & MOTOR_R) == MOTOR_R) & ((actorsImage & MOTOR_L) == MOTOR_L) ) { // check switching to MOTOR_R if MOTOR_L is enabeled
        clearBitInOutput(MOTOR_L);
        applyProcessToOutput();
    }else if ( ((mask & MOTOR_L) == mask) & ((actorsImage & MOTOR_R) == MOTOR_R) ) { // other way around
        clearBitInOutput(MOTOR_R);
        applyProcessToOutput();
    }else;
    
    actorsImage = actorsImage | mask;
}

void clearBitInOutput(Image mask) { // gets bitmask and deletes these bits in processimage (actors)
    actorsImage = actorsImage & (~mask);
}

void resetOutputs () { // sets all actors to a save value and writes to output ports (e.g. E-Stop)
    actorsImage = E_SAVE;
    
    printf("\n \n -----RESET FUNCTION TRIGGERED----- \n \n");
}


int isBitSet(Image mask) {          // DEPRICATED: gets bitmask, checks if these bits are set in process
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