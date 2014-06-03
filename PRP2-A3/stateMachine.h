/*
 * file: stateMachine.c
 * project: BScMech2-SoSe14-PRP2
 * version: 2.2.1 (03.06.2014 12:30)
 * - 0.1 first version
 * - 0.2 first and bugs fixed
 * - 0.3 initial logic enhanced, main must not initialize currentState
 * - 1.0 tested and OK, state logic enhancements
 * - 2.0 rewritten for PRP2-A3
 * - 2.1 changes for listDatabase v1.0 + minor bug-fixes
 * - 2.2 changes for listDatabase v1.2
 * - 2.2.1 serious bug fixes for dataStore
 *
 *
 * Created by Jannik Beyerstedt
 * jannik.beyerstedt.de
 * Copyright: all code under creative commons license: CC BY-NC-SA 3.0
 *
 *
 * HAW Hamburg - Labor Programmieren 2
 * festo conveyor belt system - exercise 3
 */

#ifndef BScMech2_SoSe14_PRP2_stateMachine_h
#define BScMech2_SoSe14_PRP2_stateMachine_h


//all states: 0,    1,     2,      3,      height,   h. OK,     h. n. OK,  junction, metal no,  metal yes, 10,       11,     EMERGENCY
typedef enum {INIT, START, ACTIVE, TRANSP, TRANSP_H, TRANSP_H1, TRANSP_H0, TRANSP_J, TRANSP_M0, TRANSP_M1, AT_SLIDE, AT_END, E_STOP} States;


void theMachine();


#endif
