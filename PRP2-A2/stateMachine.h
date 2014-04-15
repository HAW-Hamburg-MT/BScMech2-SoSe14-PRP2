/*
 * file: stateMachine.h
 * project: BScMech2-SoSe14-PRP2
 * version: 0.1 (15.04.2014 15:20)
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

//all states: 0,     1,      2,      height,   h. OK,     h. nOK,    junction, metal no,  metal yes
typedef enum {START, ACTIVE, TRANSP, TRANSP_H, TRANSP_H1, TRANSP_H0, TRANSP_J, TRANSP_M0, TRANSP_M1, AT_SLIDE, AT_END} States;


void theMachine (States *currentState);


#endif
