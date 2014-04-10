/*
 * file: functions.c
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
 * festo conveyor belt system - functions library
 */

#include "functions.h"
//#include "mycbw.h"  // ONLY FOR TESTING
#include "cbw.h"

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
    
    actorOutput = actorsImage;
    cbDOut(BNR, FIRSTPORTA, actorOutput);
    actorOutput = (actorsImage >> 8);
    cbDOut(BNR, FIRSTPORTCL, actorOutput);
}


int isBitSet(Image mask) { // gets bitmask and tests whether these bits are set in process image
    Image maskedBitSet = 0x0000;
    
    maskedBitSet = sensorsImage & mask;
    
    if (maskedBitSet == mask)
        return 1;
    else
        return 0;
}

int isBitNotSet (Image mask) {
    Image maskedBitSet = 0x0000;
    
    maskedBitSet = (sensorsImage ^ mask) & mask;
    
    if (maskedBitSet == mask)
        return 1;
    else
        return 0;
}

int hasBitChanged01 (Image mask) { // TODO
    Image maskedBitSet = 0x0000;
    
    maskedBitSet = changed0to1 & mask;
    
    if (maskedBitSet == mask)
        return 1;
    else
        return 0;
}

int hasBitChanged10 (Image mask) { // TODO
    Image maskedBitSet = 0x0000;
    
    maskedBitSet = changed1to0 & mask;
    
    if (maskedBitSet == mask)
        return 1;
    else
        return 0;
}

void setBitInOutput(Image mask) { // gets bitmask and sets these bits in processimage (actors)
    actorsImage = actorsImage | mask;
}

void clearBitInOutput(Image mask) { // gets bitmask and deletes these bits in processimage (actors)
    actorsImage = actorsImage & (~mask);
}

void resetOutputs () { // sets all actors to a save value and writes to output ports (e.g. E-Stop)
    actorsImage = E_SAVE;
    
    printf("\n \n -----RESET FUNCTION TRIGGERED----- \n \n");
}