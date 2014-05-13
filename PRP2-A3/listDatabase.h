/*
 * file: listDatabase.c
 * project: BScMech2-SoSe14-PRP2
 * version: 1.0 (13.05.2014 19:30)
 * - 0.1 first version
 * - 0.2 first "basic" list functions
 * - 0.3 many safety functions added
 * - 0.4 outputList basic function
 * - 0.5 outputList ready with unique filename
 * - 1.0 major changes
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

#ifndef LISTDATABASE_H
#define	LISTDATABASE_H


#include <time.h>


typedef enum {FALSE, TRUE} Boolean;

typedef struct listMeta *list_t;        // type for your list

struct listData {                       // the data stored
    time_t inputTime;
    Boolean height;
    Boolean metal;
    time_t outputTime;
};
typedef struct listData *listDataPtr;   // type for (a pointer to) some data


/*
 * specifications:
 * list_t:  type for whole list (container with metadata)
 * node:    node of the list, points at information
 *
 * - functions, that return a pointer will return NULL if an error occurred
 * - functions of type int will return 0 if an error occurred (e.g empty list), else 1
 */

list_t initializeList ();           // starts a new list (with no nodes)
int addNodeAtEnd (list_t list);     // adds node at end of list
int addNodeAtStart (list_t list);   // adds node at start of list

listDataPtr getNodeData (list_t list, int nodeNo);

int deleteFirst (list_t list);     // deletes first node
int deleteLast (list_t list);      // deletes last node
int deleteList (list_t list);      // deletes whole list, list pointer will be NULL

int outputList(list_t list);       // prints list on screen and saves to CSV-file


#endif	/* LISTDATABASE_H */