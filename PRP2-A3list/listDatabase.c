/*
 * file: listDatabase.c
 * project: BScMech2-SoSe14-PRP2
 * version: 1.2.1 (03.06.2014 12:30)
 * - 0.1 first version
 * - 0.2 first "basic" list functions
 * - 0.3 many safety functions added
 * - 0.4 outputList basic function
 * - 0.5 outputList ready with unique filename
 * - 1.0 major changes
 * - 1.1 enhanced with prewNode pointer
 * - 1.2 addNode initializes data with given dataPtr
 * - 1.2.1 bugfix at outputList and addNode
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listDatabase.h"


struct listNode {
    listDataPtr dataPtr;
    struct listNode *nextNode;
    struct listNode *prewNode;
};
typedef struct listNode *listNodePtr;

struct listMeta {
    unsigned int length;
    listNodePtr firstNodePtr;
    listNodePtr lastNodePtr;
};
typedef struct listMeta *list_t;



list_t initializeList () {
    list_t list = malloc(sizeof(struct listMeta));
    list->length = 0;
    list->firstNodePtr = NULL;
    list->lastNodePtr = NULL;
    return list;
}


int addNodeAtEnd (list_t list, listDataPtr dataPtr) {
    if (list == NULL) { // only add nodes, if list initialized
        printf("ERROR: addNodeAtEnd: there is no list");
        return 0;
    }else {
        listNodePtr oldLastNode = list->lastNodePtr;
        
        list->lastNodePtr = malloc(sizeof(struct listNode));
        list->length += 1;
        
        if (list->firstNodePtr == NULL) { // add very first element
            list->firstNodePtr = list->lastNodePtr;
            list->lastNodePtr->nextNode = NULL;
            list->lastNodePtr->prewNode = NULL;
            list->lastNodePtr->dataPtr = dataPtr;
        }else {
            oldLastNode->nextNode = list->lastNodePtr;
            list->lastNodePtr->prewNode = oldLastNode;
            list->lastNodePtr->dataPtr = dataPtr;
        }
        return 1;
    }// end list safety
}


int addNodeAtStart (list_t list, listDataPtr dataPtr) {
    if (list == NULL) { // only add nodes, if list initialized
        printf("ERROR: addNodeAtEnd: there is no list");
        return 0;
    }else {
        listNodePtr newSecondNode = list->firstNodePtr;
        
        list->firstNodePtr = malloc(sizeof(struct listNode));
        list->length += 1;
        
        if (list->lastNodePtr == NULL) { // add very first element
            list->lastNodePtr = list->firstNodePtr;
            list->firstNodePtr->nextNode = NULL;
            list->firstNodePtr->prewNode = NULL;
            list->firstNodePtr->dataPtr = dataPtr;
        }else {                         // add second+ element
            list->firstNodePtr->nextNode = newSecondNode;
            newSecondNode->prewNode = list->firstNodePtr;
            list->firstNodePtr->dataPtr = dataPtr;
        }
        return 1;
    }// end list safety
}



listDataPtr getNodeData (list_t list, int nodeNo) {
    if (list == NULL || list->firstNodePtr == NULL) { // list safety
        printf("ERROR: getNodeData: no list or no firstNode\n");
        return NULL;
    }else {
        
        if (nodeNo == 1) {
            listNodePtr nodePtr = list->firstNodePtr;
            return nodePtr->dataPtr;
        }else if ( (nodeNo > 1) && (nodeNo <= list->length) ) {
            listNodePtr nodePtr = list->firstNodePtr;
            for (int i = 1; i < nodeNo; i++) {
                nodePtr = nodePtr->nextNode;
            }
            return nodePtr->dataPtr;
            
            
        }else if ( (nodeNo == -1) && (-nodeNo <= list->length) ) {
            listNodePtr nodePtr = list->lastNodePtr;
            return nodePtr->dataPtr;
        }else if (nodeNo < -1) {
            listNodePtr nodePtr = list->lastNodePtr;
            for (int i = 1; i < -nodeNo; i++) {
                nodePtr = nodePtr->prewNode;
            }
            return nodePtr->dataPtr;
            
            
        }else {
            printf("ERROR: getNodeData: invalid nodePos number\n");
            return NULL;
        }
    }// end list safety
}

// internal only
listNodePtr getNode (list_t list, unsigned int nodeNo) {
    if (list == NULL || list->firstNodePtr == NULL) { // list safety
        printf("ERROR: getNode: no list or no firstNode\n");
        return NULL;
    }else {
        listNodePtr nodePtr = list->firstNodePtr;
        
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


int deleteFirst (list_t list) {
    if (list == NULL || list->firstNodePtr == NULL) { // list safety
        printf("ERROR: deleteFirst: no list or no firstNode\n");
        return 0;
    }else {
        listNodePtr deletedNode = list->firstNodePtr;
        
        if (list->length > 1){
            list->firstNodePtr = list->firstNodePtr->nextNode;
            free(deletedNode->dataPtr);
            free(deletedNode);
            list->length -= 1;
            return 1;
        }else if (list->length == 1) {
            free(deletedNode->dataPtr);
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

int deleteLast (list_t list) {
    if (list == NULL || list->firstNodePtr == NULL) { // list safety
        printf("ERROR: deleteFirst: no list or no firstNode\n");
        return 0;
    }else {
        listNodePtr deletedNode = getNode(list, list->length);
        listNodePtr secondLastNode = getNode(list, list->length -1);
        
        if (list->length > 1) {
            list->lastNodePtr = secondLastNode;
            secondLastNode->nextNode = NULL;
            free(deletedNode->dataPtr);
            free(deletedNode);
            list->length -= 1;
            return 1;
        }else if (list->length == 1) {
            free(deletedNode->dataPtr);
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

int deleteList (list_t list) {
    if (list == NULL) { // list safety
        return 0;
    }else {
        //while (deleteFirst()) {;}
        
        while (list->length >= 1) {
            deleteFirst(list);
        }
        free(list);
        list = NULL;
        
        return 1;
    }// end list safety
}


int outputList (list_t list) {
    if (list == NULL || list->firstNodePtr == NULL) { // list safety
        printf("ERROR: deleteFirst: no list or no firstNode\n");
        return 0;
    }else {
        FILE *file;
        struct tm *tvar;
        
        // "dynamic" filename
        time_t tnow = time(NULL);
        tvar = localtime(&tnow);
        char filename[40];
        sprintf(filename, "prpOutput_%04i%02i%02iT%02i%02i%02i.csv", tvar->tm_year+1900, tvar->tm_mon+1, tvar->tm_mday, tvar->tm_hour, tvar->tm_min, tvar->tm_sec);
        
        file = fopen(filename, "w");
        if (file == NULL) { // output safety
            printf("ERROR: outputListe: can not create file output\n");
            return 0;
        }else {// normal operation
            
            fprintf(file, "item No.; input time; height ok (Y/N); metal (Y/N); output time\n");
            printf( "\nitem No.; input time;           height ok (Y/N); metal (Y/N); output time\n");
            
            for (int i = 1; i <= list->length; i++) {//every node
                listDataPtr data = getNodeData(list, i);
                
                // print item number
                fprintf(file, "%02i;", i);
                printf("%02i;       ", i);
                
                tvar = localtime(&data->inputTime);
                fprintf(file, "%04i-%02i-%02i T%02i:%02i:%02i;",tvar->tm_year+1900, tvar->tm_mon+1, tvar->tm_mday, tvar->tm_hour, tvar->tm_min, tvar->tm_sec);
                printf("%04i-%02i-%02i T%02i:%02i:%02i; ",tvar->tm_year+1900, tvar->tm_mon+1, tvar->tm_mday, tvar->tm_hour, tvar->tm_min, tvar->tm_sec);
                
                fprintf(file, "%i;", (Boolean) data->height);
                printf("%i;               ", (Boolean) data->height);
                fprintf(file, "%i;", (Boolean) data->metal);
                printf("%i;           ", (Boolean) data->metal);
                
                tvar = localtime(&data->outputTime);
                fprintf(file, "%04i-%02i-%02i T%02i:%02i:%02i;",tvar->tm_year+1900, tvar->tm_mon+1, tvar->tm_mday, tvar->tm_hour, tvar->tm_min, tvar->tm_sec);
                printf("%04i-%02i-%02i T%02i:%02i:%02i; ",tvar->tm_year+1900, tvar->tm_mon+1, tvar->tm_mday, tvar->tm_hour, tvar->tm_min, tvar->tm_sec);
                
                fprintf(file, "\n");
                printf("\n");
            }
            
            fclose(file);
            printf("\n");
            printf("INFO: list saved\n");
            printf("\n\n");
            
        }// end output safety
        
        
        return 1;
    }// end list safety
}
