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
    addNodeAtEnd();
    
    addNodeAtStart();
    
    addDataToLastNode(50, TRUE, FALSE, 100);
    
    time(getData(1, 1)); // save current time to 1st node, 1st cell
    
    
    time_t var = *(time_t *)getData(1, 1);
    
    
    printf("%s", ctime(&var));
    
    return 0;
}

