/* Kunal Shah kgshah@ucsc.edu
 * File:   LinkedListTest.c
 * Author: kgshah
 *
 * Created on January 31, 2022, 6:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "BOARD.h"
#include "LinkedList.h"

/*
 * 
 */
int main() {
    BOARD_Init();
    
    ListItem *CList;//Create ListItem pointer
    ListItem *DList;//Create ListItem pointer
    ListItem *TList;//Create ListItem pointer
    
    CList = LinkedListNew("First:a");//test case for new list
    DList = CList;
    if (CList->data == "First:a" && CList->previousItem == NULL){
        printf("\nSUCCESS:New List Created");
    }else{
        printf("\nFAILED:New List Created");
    }
    
    CList = LinkedListCreateAfter(CList, "Second:b");//Create After test cases
    if (CList->data == "Second:b" && CList->nextItem == NULL && CList->previousItem->data == "First:a"){
        printf("\nSUCCESS:Second Item Added with NULL afterwards");
    }else{
        printf("\nFAILED:Second Item Added with NULL afterwards");
    }
    
    char* item = LinkedListRemove(DList);//Delete element in list test cases
    if (CList->previousItem == NULL && item == "First:a"){
        printf("\nSUCCESS:Deleted %s which has NULL before",item);
    }else{
        printf("\nFAILED:Deleted %s",item);
    }
        
    int listsize = LinkedListSize(CList);//List Size test function
    if (listsize == 1){
        printf("\nSUCCESS:List is size %d",listsize);
    }else{
        printf("\nFAILED:List is size %d",listsize);
    }
    
    CList = LinkedListCreateAfter(CList, "First:a");
    CList = LinkedListCreateAfter(CList, "Third:c");
    if(LinkedListGetFirst(CList)->previousItem == NULL){//First item finder test
        printf("\nSUCCESS:LinkedListGetFirst in List of Size 3");
    }else{
        printf("\nFAILED:LinkedListGetFirst in List of Size 3");
    }
    
    if(LinkedListGetLast(CList)->nextItem == NULL){//Last item finder test
        printf("\nSUCCESS:LinkedListGetLast in List of Size 3");
    }else{
        printf("\nFAILED:LinkedListGetLast in List of Size 3");
    }
    
    CList = LinkedListGetFirst(CList);//Swap list elements test cases
    DList = LinkedListGetLast(DList);
    LinkedListSwapData(CList,DList);
    if (CList->previousItem == NULL && DList->nextItem == NULL){
        printf("\nSUCCESS:Swapping front most and backmost List Items");
    }else{
        printf("\nFAILED:Swapping front most and backmost List Items");
    }
    
    CList = LinkedListCreateAfter(LinkedListGetFirst(CList), "Fourth:d");//Create After test cases#2
    if (CList->data == "Fourth:d" && CList->previousItem->data == "Third:c" && CList->nextItem->data == "First:a"){
        printf("\nSUCCESS:Item Added with another List Item before and after");
    }else{
        printf("\nFAILED:Second Item Added");
    }
    
    listsize = LinkedListSize(CList);//List Size test function
    if (listsize == 4){
        printf("\nSUCCESS:List is size %d",listsize);
    }else{
        printf("\nFAILED:List is size %d",listsize);
    }
    
    CList = LinkedListGetFirst(CList);//Delete item with values on both sides
    DList = CList->nextItem;
    CList = CList->nextItem;
    CList = CList->nextItem;
    LinkedListRemove(DList);
    if (CList->previousItem->data == "Third:c" && CList->nextItem->data == "Second:b" && CList->data == "First:a"){
        printf("\nSUCCESS:Deleted Item without adjacent NULL");
    }else{
        printf("\nFAILED:Deleted Item without adjacent NULL");
    }
    
    CList = LinkedListGetFirst(CList);
    CList = LinkedListCreateAfter(LinkedListGetFirst(CList), "Fifth:e");
    CList = LinkedListGetFirst(CList);
    CList = CList->nextItem;
    DList = CList->nextItem;
    LinkedListSwapData(CList,DList);
    if (CList->previousItem->data == "Third:c" && DList->nextItem->data == "Second:b"){
        printf("\nSUCCESS:Swapping Non-front and back");
    }else{
        printf("\nFAILED:Swapping Non-front and back");
    }
    
    TList = LinkedListNew("First:a");//test case for new list
    if (TList->data == "First:a" && TList->previousItem == NULL){
        printf("\nSUCCESS:Separate New List Created");
    }else{
        printf("\nFAILED:Separate New List Created");
    }
    
    listsize = LinkedListSize(NULL);//List Size test function
    if (listsize == 0){
        printf("\nSUCCESS:Empty List is size %d",listsize);
    }else{
        printf("\nFAILED:Empty List is size %d",listsize);
    }
    
    if(LinkedListGetFirst(TList)!= NULL && LinkedListGetFirst(TList)->data == "First:a"){//First item finder test
        printf("\nSUCCESS:LinkedListGetFirst in List of Size 1");
    }else{
        printf("\nFAILED:LinkedListGetFirst in List of Size 1");
    }
    
    if(LinkedListGetLast(TList) != NULL && LinkedListGetLast(TList)->data =="First:a"){//Last item finder test
        printf("\nSUCCESS:LinkedListGetLast in List of Size 1");
    }else{
        printf("\nFAILED:LinkedListGetLast in List of Size 1");
    }
    
    printf("\nIf next 2 lines are identical then list print works.\n");
    LinkedListPrint(CList);//List Print Test Cases
    printf("\n[Third:c,First:a,Fifth:e,Second:b]");
    
    //Below is my personal use test cases, I do not recommend using these
    /*printf("\n#################################################################");
    // (*item).data item->
    ListItem *CList;//item == NULL
    ListItem *DList;
    ListItem *TList;
    
    CList = LinkedListNew("aa");
    CList = LinkedListCreateAfter(CList, "b");
    CList = LinkedListCreateAfter(CList, "cc");
    CList = LinkedListCreateAfter(CList, "d");
    CList = LinkedListCreateAfter(CList, "d");
    CList = LinkedListCreateAfter(CList, "ee");
    CList = LinkedListCreateAfter(CList, "f");
    
    printf("\n[%s,",CList->data);
    CList = CList->previousItem;
    printf("%s,",CList->data);
    CList = CList->previousItem;
    printf("%s,",CList->data);
    CList = CList->previousItem;
    printf("%s,",CList->data);
    CList = CList->previousItem;
    printf("%s,",CList->data);
    CList = CList->previousItem;
    printf("%s,",CList->data);
    CList = CList->previousItem;
    printf("%s]\n",CList->data);
    
    printf("[%s,",CList->data);
    CList = CList->nextItem;
    printf("%s,",CList->data);
    CList = CList->nextItem;
    printf("%s,",CList->data);
    CList = CList->nextItem;
    printf("%s,",CList->data);
    CList = CList->nextItem;
    printf("%s,",CList->data);
    CList = CList->nextItem;
    printf("%s,",CList->data);
    CList = CList->nextItem;
    printf("%s]\n",CList->data);
    
    CList = CList->previousItem;
    CList = CList->previousItem;
    DList = CList->previousItem;
    LinkedListRemove(DList);
    CList = CList->previousItem;
    CList = CList->previousItem;
    CList = CList->previousItem;
    
    printf("[%s,",CList->data);
    CList = CList->nextItem;
    printf("%s,",CList->data);
    CList = CList->nextItem;
    printf("%s,",CList->data);
    CList = CList->nextItem;
    printf("%s,",CList->data);
    CList = CList->nextItem;
    printf("%s,",CList->data);
    CList = CList->nextItem;
    printf("%s]\n",CList->data);
    
    printf("[%s,",CList->data);
    CList = CList->previousItem;
    printf("%s,",CList->data);
    CList = CList->previousItem;
    printf("%s,",CList->data);
    CList = CList->previousItem;
    printf("%s,",CList->data);
    CList = CList->previousItem;
    printf("%s,",CList->data);
    CList = CList->previousItem;
    printf("%s]\n",CList->data);
    
    int ctt = LinkedListSize(CList);
    printf("ListLen(%d)",ctt);
    CList = CList->nextItem;
    ctt = LinkedListSize(CList);
    printf("\nListLen(%d)",ctt);
    
    CList = CList->nextItem;
    CList = CList->nextItem;
    CList = LinkedListGetFirst(CList);
    printf("\n[%s,",CList->data);
    CList = CList->nextItem;
    printf("%s,",CList->data);
    CList = CList->nextItem;
    printf("%s,",CList->data);
    CList = CList->nextItem;
    printf("%s,",CList->data);
    CList = CList->nextItem;
    printf("%s,",CList->data);
    CList = CList->nextItem;
    printf("%s]\n",CList->data);
    
    CList = CList->previousItem;
    CList = CList->previousItem;
    CList = CList->previousItem;
    CList = CList->previousItem;
    CList = LinkedListGetLast(CList);
    printf("[%s,",CList->data);
    CList = CList->previousItem;
    printf("%s,",CList->data);
    CList = CList->previousItem;
    printf("%s,",CList->data);
    CList = CList->previousItem;
    printf("%s,",CList->data);
    CList = CList->previousItem;
    printf("%s,",CList->data);
    CList = CList->previousItem;
    printf("%s]\n",CList->data);
    
    LinkedListSwapData(LinkedListGetFirst(CList),LinkedListGetLast(CList));
    printf("[%s,",CList->data);
    CList = CList->nextItem;
    printf("%s,",CList->data);
    CList = CList->nextItem;
    printf("%s,",CList->data);
    CList = CList->nextItem;
    printf("%s,",CList->data);
    CList = CList->nextItem;
    printf("%s,",CList->data);
    CList = CList->nextItem;
    printf("%s]\n",CList->data);
    
    LinkedListPrint(CList);*/
    
    while(1);
}

