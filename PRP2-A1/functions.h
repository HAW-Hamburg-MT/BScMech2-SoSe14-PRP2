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


#ifndef BScMech1_SoSe14_PRP2_functions_h
#define BScMech1_SoSe14_PRP2_functions_h

#include <stdio.h>

//#include "cbw.h"
#include "mycbw.h"


#define E_SAVE 0x288     // motorStop + Light_RD + LED_Reset - evtl 0x298 (junction open)
#define MASK_01  0x510   // bitmask for sensors which are only relevant when switchning from 0 -> 1
#define MASK_10  0x28f   // bitmask for sensors which are only relevant when switchning from 1 -> 0
#define MASK_ALL 0x8eb60 // bitmask for sensors which are relevant in all states

// bitmasks for actors and sensors
#define MOTOR_R    0x001
#define MOTOR_L    0x002
#define MOTOR_SLOW 0x004
#define MOTOR_STOP 0x008
#define JUNCTION   0x010
#define LIGHT_GN   0x020
#define LIGHT_YE   0x040
#define LIGHT_RD   0x080
#define LED_START  0x100
#define LED_RESET  0x200
#define LED_Q1     0x400
#define LED_Q2     0x800

#define POS_IN     0x001
#define POS_HEIGHT 0x002
#define HEIGHT_OK  0x004
#define POS_SWITCH 0x008
#define METAL_ST   0x010
#define JUNCT_ST   0x020
#define RAMPS_ST   0x040
#define POS_OUT    0x080
#define START      0x100
#define STOP       0x200
#define RESET      0x400
#define ESTOP      0x800

typedef unsigned short Image;


void initializeSystem ();       // initializes all ports
void updateProcessImage ();     // writes all sensor values to local process image
void updateProcessImage2();     // writes all sensor values to local process image AND sorts by 0->1 and 1->0 changes
void applyProcessToOutput ();   // writes local process image actor states to output ports

int isBitSet (Image mask);          // gets bitmask and tests whether these bits are set in process image
void setBitInOutput (Image mask);   // gets bitmask and sets these bits in processimage (actors)
void clearBitInOutput (Image mask); // gets bitmask and deletes these bits in processimage (actors)
void resetOutputs ();               // sets all actors to a save value and writes to output ports (e.g. E-Stop)


#endif