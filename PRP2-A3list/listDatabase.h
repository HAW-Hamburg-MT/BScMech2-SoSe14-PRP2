/*
 * file: listDatabase.h
 * project: BScMech2-SoSe14-PRP2
 * version: 0.2 (29.04.2014 15:30)
 * - 0.1 first version
 * - 0.2 first "basic" list functions
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

void initializeList ();
void addNodeAtEnd ();
void addNodeAtStart ();

void addDataToLastNode (time_t a, Boolean b, Boolean c, time_t d) ;
void addDataToLastNode2 (int pos, void *info);
struct listNode *  getNode (unsigned int pos);
void * getData (unsigned int pos, unsigned int cell);

int deleteFirst ();
int deleteLast ();
int deleteList ();



#endif	/* LISTDATABASE_H */