/*
 * file: listDatabase.h
 * project: BScMech2-SoSe14-PRP2
 * version: 0.5 (05.05.2014 14:00)
 * - 0.1 first version
 * - 0.2 first "basic" list functions
 * - 0.3 many safety functions added
 * - 0.4 outputList basic function
 * - 0.5 outputList ready with unique filename
 *
 *
 * Created by Jannik Beyerstedt
 * jannik.beyerstedt.de
 * Copyright: all code under creative commons license: CC BY-NC-SA 3.0
 *
 *
 * HAW Hamburg - Labor Programmieren 3
 * festo conveyor belt system - exercise 3
 */


#ifndef LISTDATABASE_H
#define	LISTDATABASE_H


typedef enum {FALSE, TRUE} Boolean;


/*
 * specifications:
 * list:    whole list (container with metadata)
 * node:    set of information, has a number of cells (starting with 1)
 * cell:    information storage point in a specific node (starting with 1)
 * cell 1:  time_t inputTime
 * cell 2:  Boolean height
 * cell 3:  Boolean metal
 * cell 4:  time_h outputTime
 * - information are transferred as void pointers
 * - you should do an expicit type transformation to get the "right" pointer type
 * - functions, that return a pointer will return NULL if an error occurred
 * - functions with type int will return 0 if an error occurred (e.g empty list), else 1
 */

int initializeList ();      // starts a new list (with no nodes)
int addNodeAtEnd ();        // adds empty node at end of list
int addNodeAtStart ();      // adds empty node at start of list

int addDataToLastNode (int cellNo, void *info);               // stores information (pass pointer) in "cell" (1-4)
struct listNode * getNode (unsigned int nodeNo);              // returns pointer to node "nodeNo"
void * getData (unsigned int nodeNo, unsigned int cellNo);    // returns pointer to a data cell

int deleteFirst ();     // deletes first node
int deleteLast ();      // deletes last node
int deleteList ();      // deletes all node and then the list container itself

int outputList();       // prints list on screen ans saves to CSV-file


#endif	/* LISTDATABASE_H */