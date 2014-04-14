/*
 * file: systemFunctions.h
 * project: BScMech2-SoSe14-PRP2
 * version: 1.1 (14.04.2014 21:30)
 * - 0.9 first Version (not tested with real machine)
 * - 1.0 stable and tested for PRP2-A1
 * - 1.1 motor safety added
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

#ifndef BScMech2_SoSe14_PRP2_systemFunctions_h
#define BScMech2_SoSe14_PRP2_systemFunctions_h

#define BNR 0

#define E_SAVE 0x088      // safe/ reset actors state (motorStop + Light_RD)

// bitmasks for actors and sensors
#define MOTOR_R    0x0001
#define MOTOR_L    0x0002
#define MOTOR_SLOW 0x0004
#define MOTOR_STOP 0x0008
#define JUNCTION   0x0010 // the junction is closed normally
#define LIGHT_GN   0x0020
#define LIGHT_YE   0x0040
#define LIGHT_RD   0x0080
#define LED_START  0x0100
#define LED_RESET  0x0200
#define LED_Q1     0x0400
#define LED_Q2     0x0800

#define POS_IN     0x0001 // NC: light barrier
#define POS_HEIGHT 0x0002 // NC: light barrier
#define SNS_HEIGHT 0x0004 // NO: closed if height is in range
#define POS_JUNCT  0x0008 // NC: light barrier
#define SNS_METAL  0x0010 // NO: closed if metal detected
#define SNS_JUNCT  0x0020 // NO: closed if junction open
#define SNS_SLIDE  0x0040 // NC: light barrier - open if slide is full
#define POS_OUT    0x0080 // NC: light barrier
#define BUT_START  0x0100 // NO
#define BUT_STOP   0x0200 // NC
#define BUT_RESET  0x0400 // NO
#define BUT_ESTOP  0x0800 // NC: emergency stop is NC

// 0101.0011.0100 mask for all NO sensors
#define SENSORS_NO 0x0534
// 1010.1100.1011 mask for all NC sensors
#define SENSORS_NC 0x0acb

// 1111.1101.1011 mask for all sensors where hasTriggered is valid
#define HAS_TRIG_VALID 0x0fdb
// 1000.1110.1111 mask for sensors where isTriggered is valid
#define IS_TRIG_VALID  0x08ef


typedef unsigned short Image;


void initializeSystem ();       // initializes all ports
void updateProcessImage();      // writes all sensor values to local process image AND sorts by 0->1 and 1->0 changes
void applyProcessToOutput ();   // writes local process image actor states to output ports

int hasTriggered (Image mask);      // NEW: checks whether some sensor has changed it´s state (0->1, 1->0); ERROR -1 is not valid
int isTriggered (Image mask);       // NEW: checks whether some sensor has active/ triggered state; ERROR -1 if not valid

void setBitInOutput (Image mask);   // gets bitmask and sets these bits in processimage (actors)
void clearBitInOutput (Image mask); // gets bitmask and deletes these bits in processimage (actors)
void resetOutputs ();               // sets all actors to a save value and writes to output ports (e.g. E-Stop)

int isBitSet (Image mask);          // DEPRICATED: gets bitmask, checks if these bits are set in process
int isBitNotSet (Image mask);       // DEPRICATED: gets bitmask, checks if all bits are not set process (IS NEEDED)


#endif
