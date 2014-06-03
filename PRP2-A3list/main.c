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
    list_t itemsList = NULL;
    listDataPtr dataStore = NULL;
    
    
    itemsList = initializeList();
    
    
    dataStore = malloc(sizeof(struct listData));
    
    time(&dataStore->inputTime);
    dataStore->height = TRUE;
    dataStore->metal = FALSE;
    time(&dataStore->outputTime);
    
    addNodeAtEnd(itemsList, dataStore);
    dataStore = NULL;
    
    
    
    dataStore = malloc(sizeof(struct listData));
    
    time(&dataStore->inputTime);
    dataStore->height = TRUE;
    dataStore->metal = FALSE;
    time(&dataStore->outputTime);
    
    addNodeAtEnd(itemsList, dataStore);
    dataStore = NULL;
    
    
    
    outputList(itemsList);
    
    
    return 1;
}

