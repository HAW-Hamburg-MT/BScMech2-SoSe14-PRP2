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


#ifndef functions_h
#define functions_h

#include <stdio.h>

#define BNR 0

#define E_SAVE 0x088     // motorStop + Light_RD
#define MASK_01  0x510   // bitmask for sensors which are only relevant when switchning from 0 -> 1
#define MASK_10  0x28f   // bitmask for sensors which are only relevant when switchning from 1 -> 0
#define MASK_ALL 0x8eb60 // bitmask for sensors which are relevant in all states

// bitmasks for actors and sensors
#define MOTOR_R    0x0001
#define MOTOR_L    0x0002
#define MOTOR_SLOW 0x0004
#define MOTOR_STOP 0x0008
#define JUNCTION   0x0010
#define LIGHT_GN   0x0020
#define LIGHT_YE   0x0040
#define LIGHT_RD   0x0080
#define LED_START  0x0100
#define LED_RESET  0x0200
#define LED_Q1     0x0400
#define LED_Q2     0x0800

#define POS_IN     0x0001
#define POS_HEIGHT 0x0002
#define HEIGHT_OK  0x0004
#define POS_JUNCT  0x0008
#define METAL_ST   0x0010
#define JUNCT_ST   0x0020
#define SLIDE_ST   0x0040
#define POS_OUT    0x0080
#define START      0x0100
#define STOP       0x0200
#define RESET      0x0400
#define ESTOP      0x0800

typedef unsigned short Image;


void initializeSystem ();       // initializes all ports
void updateProcessImage();      // writes all sensor values to local process image AND sorts by 0->1 and 1->0 changes
void applyProcessToOutput ();   // writes local process image actor states to output ports

int isBitSet (Image mask);          // gets bitmask and tests whether these bits are set in process image
int isBitNotSet (Image mask);
int hasBitChanged01 (Image mask);
int hasBitChanged10 (Image mask);

void setBitInOutput (Image mask);   // gets bitmask and sets these bits in processimage (actors)
void clearBitInOutput (Image mask); // gets bitmask and deletes these bits in processimage (actors)
void resetOutputs ();               // sets all actors to a save value and writes to output ports (e.g. E-Stop)


#endif