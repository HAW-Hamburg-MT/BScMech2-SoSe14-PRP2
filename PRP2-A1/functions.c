/*
 * file: functions.c
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
 * festo conveyor belt system - functions library
 */

#include "functions.h"


Image actorsImage = 0x0000;
Image sensorsImage = 0x0000;
Image lastReadingImage = 0x0000;


void initializeSystem() {
    cbDConfigPort(BNR, FIRSTPORTA, DIGITALOUT);
    cbDConfigPort(BNR, FIRSTPORTB, DIGITALIN);
    cbDConfigPort(BNR, FIRSTPORTCL, DIGITALOUT);
    cbDConfigPort(BNR, FIRSTPORTCH, DIGITALIN);
}

void updateProcessImage() { // writes all sensor values to local process image
    Byte reading = 0x00;
    cbDIn(BNR, FIRSTPORTB, &reading);
    sensorsImage = reading;
    cbDIn(BNR, FIRSTPORTCH, &reading);
    sensorsImage += (reading << 8);
    
    printf("sensors = 0x%x \n", sensorsImage);
}

void updateProcessImage2() { // writes all sensor values to local process image AND sorts by 0->1 and 1->0 changes
    Byte reading = 0x00;
    Image readingImage = 0x0000;
    Image changed0to1 = 0x0000;
    Image changed1to0 = 0x0000;
    Image changedYes = 0x0000;
    
    cbDIn(BNR, FIRSTPORTB, &reading);
    readingImage = reading;
    cbDIn(BNR, FIRSTPORTCH, &reading);
    readingImage += (reading << 8);
    
    // 0 to 1
    changedYes = lastReadingImage ^ readingImage;
    changed0to1 = changedYes & readingImage;
    
    // 1 to 0
    changedYes = lastReadingImage ^ readingImage;
    changed1to0 = changedYes & lastReadingImage;
    
    // mask changes and write to process image
    sensorsImage = (changed0to1 & MASK_01) + (changed1to0 & MASK_10) + (readingImage & MASK_ALL);
    lastReadingImage = readingImage;
    
    printf("--updProcsImg2:  sensors = 0x%3x \n", sensorsImage);
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

void setBitInOutput(Image mask) { // gets bitmask and sets these bits in processimage (actors)
    actorsImage = actorsImage | mask;
    
    printf("--setBitInOutput:   mask = 0x%3x  new Image = 0x%3x \n", mask, actorsImage);
}

void clearBitInOutput(Image mask) { // gets bitmask and deletes these bits in processimage (actors)
    actorsImage = actorsImage & (~mask);
    
    printf("--clearBitInOutput: mask = 0x%3x  new Image = 0x%3x \n", mask, actorsImage);
}

void resetOutputs () { // sets all actors to a save value and writes to output ports (e.g. E-Stop)
    actorsImage = E_SAVE;
    updateProcessImage();
    
    printf("\n \n -----RESET FUNCTION TRIGGERED----- \n \n");
}