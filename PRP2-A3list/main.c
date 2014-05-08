/*
 * file: main.c
 * project: BScMech2-SoSe14-PRP2
 * version: 0.2 (27.04.2014 14:30)
 * - 0.1 first version
 * - 0.2 updated for output
 *
 *
 * Created by Jannik Beyerstedt
 * jannik.beyerstedt.de
 * Copyright: all code under creative commons licence: CC BY-NC-SA 3.0
 *
 *
 * HAW Hamburg - Labor Programmieren 3
 * festo conveyor belt system - excercise 3
 * FOR TESTING listDatabase.h
 */

#include <stdio.h>
#include "listDatabase.h"
#include <time.h>

int main()
{
    
    initializeList();
    
    addNodeAtEnd();
    addNodeAtStart();
    
    int info = 50;
    addDataToLastNode(1, &info);
    Boolean info2 = TRUE;
    addDataToLastNode(2, &info2);
    info2 = FALSE;
    addDataToLastNode(3, &info2);
    info = 100;
    addDataToLastNode(4, &info);
    
    
    time(getData(1, 1)); // save current time to 1st node, 1st cell
    
    outputList();
    
    
    return 1;
}

