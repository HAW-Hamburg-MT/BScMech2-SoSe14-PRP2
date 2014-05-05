//
//  main.c
//  PRP2-A3list
//
//  Created by Jannik Beyerstedt on 29.04.14.
//  Copyright (c) 2014 Jannik Beyerstedt. All rights reserved.
//

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

