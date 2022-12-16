/* Kunal Shah kgshah@ucsc.edu
 * File:   LinkedList.c
 * Author: kgshah
 *
 * Created on January 31, 2022, 6:39 PM
 */

#include "LinkedList.h"
#include "stdlib.h"
#include "BOARD.h"
#include "stdio.h"

ListItem *LinkedListNew(char *data){
    if (data == NULL){//check for null input
        return NULL;
    }
    struct ListItem* CList = malloc(sizeof(struct ListItem));//creating ListItem
    if (CList == NULL){//check for null input
        return NULL;
    }
    CList->data = data;//adding data to this list item
    CList->nextItem = NULL;//telling list item it is first item
    CList->previousItem = NULL;//telling list item its is last item
    return CList;//returning pointer to this list item
}

ListItem *LinkedListCreateAfter(ListItem *item, char *data){
    if (item == NULL){//check for null input
        return NULL;
    }
    struct ListItem* CList = malloc(sizeof(struct ListItem));//creating ListItem
    if (CList == NULL){//check for null list
        return NULL;
    }
    CList->data = data;//writing data to list item
    CList->nextItem = item->nextItem;//inserting this list in correct position
    CList->previousItem = item;//inserting this list in correct position cont.
    item->nextItem = CList;//inserting this list in correct position cont.
    return CList;
}

char *LinkedListRemove(ListItem *item){
    if (item == NULL){//check for null input
        return NULL;
    }
    ListItem* PList = item->previousItem;//set PList to patch gap
    ListItem* NList = item->nextItem;//set PList to patch gap
    if (PList == NULL && NList == NULL){//if this is last item in list then no need to patch up the list
        char* ptr = item->data;
        free(item);
        return ptr;
    }
    if (PList != NULL){//Check that there is indeed something before this listitem
        PList->nextItem = item->nextItem;
    }else{
        NList->previousItem = NULL;
    }
    if (NList != NULL){//Check that there is indeed something after this listitem
        NList->previousItem = item->previousItem;
    }else{
        PList->nextItem = NULL;
    }
    
    char* ptr = item->data;//saving data ptr to var ptr
    free(item);//relieving memory
    return ptr;//returning data ptr
}

int LinkedListSize(ListItem *list){
    if (list == NULL){//check for null input
        return 0;
    }
    ListItem* PList = list->previousItem;
    if (PList == NULL){
        PList = list;
    }
    while (PList->previousItem != NULL){
            PList = PList->previousItem;
    }
    int ListLen = 1;
    while(PList->nextItem != NULL){
        ListLen++;
        PList = PList->nextItem;
    }
    return ListLen;
}

ListItem *LinkedListGetFirst(ListItem *list){
    if (list == NULL){//check for null input
        return NULL;
    }
    ListItem* PList = list->previousItem;//setting PList to iterate
    if (PList == NULL){//checking previous item was not NULL/First Item
        PList = list;
    }
    while (PList->previousItem != NULL){//iterating backwards through the list until we reach the first item
            PList = PList->previousItem;
    }
    return PList;//return ptr to first item in list
}

ListItem *LinkedListGetLast(ListItem *list){
    if (list == NULL){//check for null input
        return NULL;
    }
    ListItem* NList = list->nextItem;//setting NList to iterate
    if (NList == NULL){//checking next item was not NULL/Last Item
        NList = list;
    }
    while (NList->nextItem != NULL){//iterating through the list until we reach the Last item
            NList = NList->nextItem;
    }
    return NList;//return the ptr to Last Item
}

int LinkedListSwapData(ListItem *firstItem, ListItem *secondItem){
    if (firstItem == NULL || secondItem == NULL){//check neither are NULL items
        return STANDARD_ERROR;
    }
    char* dataptr = firstItem->data;//storing first items data to item
    firstItem->data = secondItem->data;//storing 2nd's data to first
    secondItem->data = dataptr;//storing 1st's data to second using dataptr var
    return SUCCESS;
}

int LinkedListPrint(ListItem *list){
    if (list == NULL){//check for null input
        return STANDARD_ERROR;
    }
    ListItem* CList = list->previousItem;
    if (CList == NULL){//checking previous item was not NULL/First Item
        CList = list;
    }
    while (CList->previousItem != NULL){//iterating backwards through the list until we reach the first item
            CList = CList->previousItem;
    }
    printf("[");//prinf starting bracket like python list
    while (CList->nextItem != NULL){//while loop to iterate thru each listitem
        printf("%s,",CList->data);//print item and comma
        CList = CList->nextItem;//iterate to next list item
    }
    printf("%s]",CList->data);//print last item with ending bracket
    return SUCCESS;
}