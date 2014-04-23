/*
 * file: stateMachine.h
 * project: BScMech2-SoSe14-PRP2
 * version: 1.0 (22.04.2014 15:00)
 * - 0.1 first version
 * - 0.2 first and bugs fixed
 * - 0.3 initial logic enahnced, main must not initialize currentState
 * - 1.0 tested and OK, state logic enhancements
 *
 *
 * Created by Jannik Beyerstedt
 * jannik.beyerstedt.de
 * Copyright: all code under creative commons license: CC BY-NC-SA 3.0
 *
 *
 * HAW Hamburg - Labor Programmieren 2
 * festo conveyor belt system - exercise 2
 */

#ifndef BScMech2_SoSe14_PRP2_stateMachine_h
#define BScMech2_SoSe14_PRP2_stateMachine_h

//all states: 0,    1,     2,      3,      height,   h. OK,     h. n. OK,  junction, metal no,  metal yes
typedef enum {INIT, START, ACTIVE, TRANSP, TRANSP_H, TRANSP_H1, TRANSP_H0, TRANSP_J, TRANSP_M0, TRANSP_M1, AT_SLIDE, AT_END} States;


void theMachine();


#endif
