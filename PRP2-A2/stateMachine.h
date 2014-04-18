/*
 * file: stateMachine.h
 * project: BScMech2-SoSe14-PRP2
 * version: 0.3 (18.04.2014 11:30)
 * - 0.1 first version
 * - 0.2 first and bugs fixed
 * - 0.3 inital logic enahnced, main must not initialize currentState
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

#ifndef BScMech2_SoSe14_PRP2_stateMachine_h
#define BScMech2_SoSe14_PRP2_stateMachine_h

//all states: 0,     1,      2,      height,   h. OK,     h. n. OK,  junction, metal no,  metal yes
typedef enum {START, ACTIVE, TRANSP, TRANSP_H, TRANSP_H1, TRANSP_H0, TRANSP_J, TRANSP_M0, TRANSP_M1, AT_SLIDE, AT_END} States;


void theMachine (States *currentState);


#endif
