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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef enum {FALSE, TRUE} Boolean;

struct listNode {
    time_t inputTime;
    Boolean height;
    Boolean metal;
    time_t outputTime;
    struct listNode *nextNode;
};

struct listValues {
    unsigned int length;
    struct listNode *firstNodePtr;
    struct listNode *lastNodePtr;
};

struct listValues *list = NULL;


void initializeList () {
    list = malloc(sizeof(struct listValues));
    list->length = 0;
    list->firstNodePtr = NULL;
    list->lastNodePtr = NULL;
}

void addDataToLastNode (time_t a, Boolean b, Boolean c, time_t d) {
    list->lastNodePtr->inputTime = a;
    list->lastNodePtr->height = b;
    list->lastNodePtr->metal = c;
    list->lastNodePtr->outputTime = d;
}

void addDataToLastNode2 (int pos, void *info) {
    switch (pos) {
        case 1:
            list->lastNodePtr->inputTime = *(time_t *)info;
            break;
        case 2:
            list->lastNodePtr->height = *(Boolean *)info;
            break;
        case 3:
            list->lastNodePtr->metal = *(Boolean *)info;
            break;
        case 4:
            list->lastNodePtr->outputTime = *(time_t *)info;
            break;
    }
}

struct listNode * getNode (unsigned int pos) {
    struct listNode *nodePtr = list->firstNodePtr;
    
    if (pos == 1) {
        return nodePtr;
    }else if (pos > 1) {
        for (int i = 1; i < pos; i++) {
            nodePtr = nodePtr->nextNode;
        }
        return nodePtr;
        
    }else {
        return NULL;
    }
}

void *getData (unsigned int pos, unsigned int cell) {
    if (pos == 0 || cell == 0) {
        return  NULL;
    }else {
        struct listNode *nodePtr = getNode(pos);
        
        switch (cell) {
            case 1:
                return &nodePtr->inputTime;
                break;
            case 2:
                return &nodePtr->height;
                break;
            case 3:
                return &nodePtr->metal;
                break;
            case 4:
                return &nodePtr->outputTime;
                break;
                
            default:
                return NULL;
                break;
        }
        
        
    }
}



void addNodeAtStart () {
    struct listNode *secondNode = list->firstNodePtr;
    
    list->firstNodePtr = malloc(sizeof(struct listNode));
    list->length += 1;
    
    if (list->lastNodePtr == NULL) { // add very first element
        list->lastNodePtr = list->firstNodePtr;
        list->firstNodePtr->nextNode = NULL;
    }else {                         // add second+ element
        list->firstNodePtr->nextNode = secondNode;
    }
}

void addNodeAtEnd () {
    struct listNode *secondLastNode = list->lastNodePtr;
    
    list->lastNodePtr = malloc(sizeof(struct listNode));
    list->length += 1;
    
    if (list->firstNodePtr == NULL) { // add very first element
        list->firstNodePtr = list->lastNodePtr;
        list->lastNodePtr->nextNode = NULL;
    }else {
        secondLastNode->nextNode = list->lastNodePtr;
    }
}

int deleteFirst () {
    struct listNode *deletedNode = list->firstNodePtr;
    
    if (list->length > 1){
        list->firstNodePtr = list->firstNodePtr->nextNode;
        free(deletedNode);
        list->length -= 1;
        return 1;
    }else if (list->length == 1) {
        free(deletedNode);
        list->firstNodePtr = NULL;
        list->lastNodePtr = NULL;
        list->length -= 1;
        return 1;
    }else {
        return 0;
    }
}

int deleteLast () {
    // TODO
    
    
    return 0;
}

int deleteList () {
    
    if (list == NULL) {
        return 0;
    }else {
        //while (deleteFirst()) {;}
        
        while (list->length >= 1) {
            deleteFirst();
        }
        free(list);
        list = NULL;
        
        return 1;
    }
}
