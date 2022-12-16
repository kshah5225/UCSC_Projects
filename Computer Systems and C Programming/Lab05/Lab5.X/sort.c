/* Kunal Shah kgshah@ucsc.edu
 * File:   sort.c
 * Author: kgshah
 *
 * Created on January 31, 2022, 6:37 PM
 */

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>

//CMPE13 Support Library
#include "BOARD.h"


// User libraries
#include "LinkedList.h"


// **** Declare any function prototypes here ***
ListItem *CreateUnsortedList(void); //this function has been written for you
ListItem *SelectionSort(ListItem* list);
ListItem *InsertionSort(ListItem* list);


/* Students should not need to modify main! */
int main(void)
{
    BOARD_Init();

    printf("\n\nWelcome to kgshah's sort.c, compiled on %s %s.\n", __DATE__, __TIME__);

    ListItem* listToSort;

    //Do a timing test 
    printf("\nStarting stopwatch for selection sort...\n");//?What do I do with the stopwatch stuff now?
    listToSort = CreateUnsortedList();
    __asm("nop"); //put a breakpoint on this line
    listToSort = SelectionSort(listToSort);
    __asm("nop"); //put a breakpoint on this line, and record the stopwatch time
    LinkedListPrint(listToSort);


    printf("\nStarting stopwatch for insertion sort...\n");
    listToSort = CreateUnsortedList();
    __asm("nop"); //put a breakpoint on this line
    listToSort = InsertionSort(listToSort);
    __asm("nop"); //put a breakpoint on this line, and record the stopwatch time
    LinkedListPrint(listToSort);

    BOARD_End();
    while (1);
    return 0;
}

/**
 * SelectionSort() performs a selection sort on a passed to it.  The list is sorted alphabetically,
 * as determined by string.h's strcmp().  
 *
 * @param list Any element in a linked list to sort.  
 * @return a pointer to the head of the sorted list.
 * 
 * SelectionSort() assumes that no list items have a NULL data member.  It also assumes that 'list'
 * is a valid, non-NULL pointer to a linked list.
 * 
 * This function does not print.
 */
ListItem *SelectionSort(ListItem* list)
{
    ListItem *CList;//define CList list item pointer
    ListItem *NList;//define NList list item pointer
    CList = LinkedListGetFirst(list);            //FU is pointer to first item
    while(CList->nextItem != NULL){              //while FU is not tail:
        NList = CList->nextItem;                 //S is pointer to FU?s nextItem
        while(NList != NULL){                    //while S is in list:
            if(strcmp(CList->data,NList->data) > 0){//if FU > S:
                LinkedListSwapData(CList,NList); //swap FU and S contents
            }                                    //
            NList = NList->nextItem;             //advance S
        }                                        //
        CList = CList->nextItem;                 //advance FU
    }                                            //
    return LinkedListGetFirst(CList);            //return pointer list start ptr
}

/**
 * InsertionSort() performs an insertion sort on a passed to it.  The list is sorted alphabetically,
 * as determined by string.h's strcmp().  
 *
 * @param list Any element in a linked list to sort.  
 * @return a pointer to the head of the sorted list.
 * 
 * SelectionSort() assumes that no list items have a NULL data member.  It also assumes that 'list'
 * is a valid, non-NULL pointer to a linked list.
 * 
 * This function does not print.
 */
ListItem *InsertionSort(ListItem* list)
{
    ListItem *FS;                           //define FS list item pointer
    ListItem *LU;                           //define LU list item pointer
    ListItem *S;                            //define S list item pointer
    char *item;     //define a temp pointer to hold items of deleted list items
    FS = LinkedListGetLast(list);           //FS = tail of list
    while (FS->previousItem != NULL){       //while FS is not head of list:
        LU = FS->previousItem;              //  LU = FS?s previous item
        if(strcmp(FS->data,LU->data) > 0){  //  if LU < FS:
                FS = LU;                    //    FS = LU
        }else{                              //  else
            S = FS;                         //    S = FS
            while(S->nextItem != NULL){     //    while (S is not tail of list):
                if (strcmp(S->nextItem->data,LU->data) > 0){
                    break;                  //      if S's next item > LU: break
                }else{                      //       else:
                    S = S->nextItem;        //         S = S's next item
                }                           //
            }                               //
            item = LinkedListRemove(LU);    //    remove LU item then
            LinkedListCreateAfter(S, item); //    re-insert after S
        }                                   //
    }                                       //
    return LinkedListGetFirst(FS);          //return pointer to start of this list
}

/* CreateUnsortedList() uses the functions in the LinkedList library to
 * generate an unsorted list.  
 * 
 * Students should not modify this function!
 * If an error occurs in this function, there is almost certainly 
 * a bug in your implementation of LinkedList.h.
 *   
 * @return A pointer to a ListItem which is the head of a new unsorted list. 
 */
ListItem *CreateUnsortedList(void)
/// <editor-fold defaultstate="collapsed" desc="CreateUnsortedList definition">
{
 char* wordList[] = {
        "decide",   "toothpaste",   "lowly",        "robin",        "reign",        "crowd",
        "pies",     "reduce",       "tendency",     "surround",     "finger",       "rake", 
        "alleged",  "hug",          "nest",         "punishment",   "eggnog",       "side", 
        "beef",     "exuberant",    "sort",         "scream",       "zip",          "hair", 
        "ragged",   "damage",       "thought",      "jump",         "frequent",     "substance",
        "head",     "step",         "faithful",     "sidewalk",     "pig",          "raspy",
        "juggle",   "shut",         "maddening",    "rock",         "telephone",    "selective",
        NULL};
    //  char* wordList[] = {"D", "A", "C", "E", "B", NULL};


    int i = 0;
    ListItem* head = LinkedListNew(wordList[i]);
    ListItem* tail = head;
    for (i = 1; wordList[i] != NULL; i++) {
        tail = LinkedListCreateAfter(tail, wordList[i]);
        if(tail == NULL){
            printf("ERROR:  Heap full! Please increase heap size.\n");
            FATAL_ERROR();
        }
    }
    return head;
}
// </editor-fold>
