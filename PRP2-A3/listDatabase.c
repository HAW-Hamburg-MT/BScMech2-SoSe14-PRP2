/*
 * file: listDatabase.c
 * project: BScMech2-SoSe14-PRP2
 * version: 0.4 (04.05.2014 21:00)
 * - 0.1 first version
 * - 0.2 first "basic" list functions
 * - 0.3 many safety functions added
 * - 0.4 outputList basic function
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

// TODO: outputList filename with date stamp

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listDatabase.h"


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



int initializeList () {
    if (list == NULL) { // only add a new list, if there is no list initialized
        list = malloc(sizeof(struct listValues));
        list->length = 0;
        list->firstNodePtr = NULL;
        list->lastNodePtr = NULL;
        return 1;
    }else {
        printf("ERROR: initializeList: there is already a list\n");
        return 0;
    }// end list safety
}

int addNodeAtEnd () {
    if (list == NULL) { // only att nodes, if list initialized
        printf("ERROR: addNodeAtEnd: there is no list");
        return 0;
    }else {
        struct listNode *secondLastNode = list->lastNodePtr;
        
        list->lastNodePtr = malloc(sizeof(struct listNode));
        list->length += 1;
        
        if (list->firstNodePtr == NULL) { // add very first element
            list->firstNodePtr = list->lastNodePtr;
            list->lastNodePtr->nextNode = NULL;
        }else {
            secondLastNode->nextNode = list->lastNodePtr;
        }
        return 1;
    }// end list safety
}

int addNodeAtStart () {
    if (list == NULL) { // only add nodes, if list initialized
        printf("ERROR: addNodeAtEnd: there is no list");
        return 0;
    }else {
        struct listNode *secondNode = list->firstNodePtr;
        
        list->firstNodePtr = malloc(sizeof(struct listNode));
        list->length += 1;
        
        if (list->lastNodePtr == NULL) { // add very first element
            list->lastNodePtr = list->firstNodePtr;
            list->firstNodePtr->nextNode = NULL;
        }else {                         // add second+ element
            list->firstNodePtr->nextNode = secondNode;
        }
        return 1;
    }// end list safety
}


int addDataToLastNode (int cellNo, void *info) {
    if (list == NULL || list->lastNodePtr == NULL) { // list safety
        printf("ERROR: addDataToLastNode: no list or no node");
        return 0;
    }else {
        switch (cellNo) {
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
            default:
                printf("ERROR: addDataToLastNode: invalid cell number\n");
                break;
        }
        return 1;
    }// end list safety
}

struct listNode * getNode (unsigned int nodeNo) {
    if (list == NULL || list->firstNodePtr == NULL) { // list safety
        printf("ERROR: getNode: no list or no firstNode\n");
        return NULL;
    }else {
        struct listNode *nodePtr = list->firstNodePtr;
        
        if (nodeNo == 1) {
            return nodePtr;
        }else if (nodeNo > 1) {
            for (int i = 1; i < nodeNo; i++) {
                nodePtr = nodePtr->nextNode;
            }
            return nodePtr;
            
        }else {
            printf("ERROR: getNode: invalid nodePos number\n");
            return NULL;
        }
    }// end list safety
}

void *getData (unsigned int nodePos, unsigned int cellPos) {
    if (nodePos == 0 || cellPos == 0 || list == NULL) {
        printf("ERROR: getData: invalis nodePos or cellPos number\n");
        return  NULL;
    }else {
        struct listNode *nodePtr = getNode(nodePos);
        if (nodePtr == NULL) { // getNode safety
            return NULL;
        }// end getNode safety
        
        switch (cellPos) {
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
                printf("ERROR: getData: other error\n");
                return NULL;
                break;
        }
    }// end position and list safety
}


int deleteFirst () {
    if (list == NULL || list->firstNodePtr == NULL) { // list safety
        printf("ERROR: deleteFirst: no list or no firstNode\n");
        return 0;
    }else {
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
    }// end list safety
}

int deleteLast () {
    if (list == NULL || list->firstNodePtr == NULL) { // list safety
        printf("ERROR: deleteFirst: no list or no firstNode\n");
        return 0;
    }else {
        struct listNode *deletedNode = getNode(list->length);
        struct listNode *secondLastNode = getNode(list->length -1);
        
        if (list->length > 1) {
            list->lastNodePtr = secondLastNode;
            secondLastNode->nextNode = NULL;
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
    }// end list safety
}

int deleteList () {
    if (list == NULL) { // list safety
        return 0;
    }else {
        //while (deleteFirst()) {;}
        
        while (list->length >= 1) {
            deleteFirst();
        }
        free(list);
        list = NULL;
        
        return 1;
    }// end list safety
}


int outputList () {
    if (list == NULL || list->firstNodePtr == NULL) { // list safety
        printf("ERROR: deleteFirst: no list or no firstNode\n");
        return 0;
    }else {
        FILE *file;
        
        // +++ TODO: "dynamic" filename
        char *filename = "test.txt";
        
        file = fopen(filename, "w");
        if (file == NULL) { // output safety
            printf("ERROR: outputListe: can not create file output\n");
            return 0;
        }else {// normal operation
            
            fprintf(file, "item No.; input time; height ok (Y/N); metal (Y/N); output time\n");
            printf( "item No.; input time; height ok (Y/N); metal (Y/N); output time\n");
            
            for (int i = 1; i <= list->length; i++) {//every node
                // print item number
                fprintf(file, "%i;", i);
                printf("%i;", i);
                
                fprintf(file, "%s;", ctime(getData(i, 1)));
                printf("%s;", ctime(getData(i, 1)));
                fprintf(file, "%i;", *(Boolean *) getData(i, 2));
                printf("%i;", *(Boolean *) getData(i, 2));
                fprintf(file, "%i;", *(Boolean *) getData(i, 3));
                printf("%i;", *(Boolean *) getData(i, 3));
                fprintf(file, "%s;", ctime(getData(i, 4)));
                printf("%s;", ctime(getData(i, 4)));
                
                fprintf(file, "/n");
                printf("/n");
            }
            
            fclose(file);
            
        }// end output safety

        
        return 1;
    }// end list safety
}
