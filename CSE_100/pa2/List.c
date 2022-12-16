//-----------------------------------------------------------------------------
// Kunal Shah, kgshah
// 2022 Spring CSE101 PA2
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   int data;
   Node next;
   Node prev;
} NodeObj;

// private List type
typedef struct ListObj* List;//I dont know what this line of code does but I added it for consistancy sake

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int index;
   int length;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      while( !isEmpty(*pL) ) { 
         deleteFront(*pL); 
      }
      free(*pL);
      *pL = NULL;
   }
}


// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L){
   return(L->length);
}

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
   return(L->index);
}

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int front(List L){
   if(isEmpty(L)){
      printf("List Error: calling front() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->front->data);
}

// back()
// Returns back element of L. 
// Pre: length()>0
int back(List L){
   if(isEmpty(L)){
      printf("List Error: calling back() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->back->data);
}

//get()
// Returns cursor element of L. 
// Pre: length()>0, index()>=0
int get(List L){
   if(isEmpty(L)){
      printf("List Error: calling get() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if(L->index<0){
      printf("List Error: calling get() while index is %d\n",L->index);
      exit(EXIT_FAILURE);
   }
   return(L->cursor->data);
}

//equals()
// Returns true iff Lists A and B are in same
// state, and returns false otherwise.
bool equals(List A, List B){
   int eq = 0;
   Node N = NULL;
   Node M = NULL;

   if( A==NULL || B==NULL ){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   //check if each length is equal one by one after checking the lengths are equal
   eq = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( eq && N!=NULL){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}


// isEmpty()
// Returns true if L is empty, otherwise returns false.
bool isEmpty(List L){
   if( L==NULL ){
      printf("List Error: calling isEmpty() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length<=0);
}


// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L){
   while (length(L) != 0){
      deleteBack(L);
   }
}

// set()
// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, int x){
   if(isEmpty(L)){
      printf("List Error: calling set() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if(L->index<0){
      printf("List Error: calling set() while index is %d\n",L->index);
      exit(EXIT_FAILURE);
   }
   L->cursor->data = x;
}

// moveFront()
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
   L->index = 0;
   L->cursor = L->front;
   if(L->front==NULL){
      L->index=-1;
   }
}

// moveBack()
// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
   if(!isEmpty(L)){
      L->index = L->length-1;
      L->cursor = L->back;
   }
}

// movePrev
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L){
   if(L->cursor==L->front||L->cursor==NULL){//if cursor is already at front or is null
      L->cursor=NULL;
      L->index=-1;
   }else{//if cursor has space to move back one element
      L->index--;
      L->cursor = L->cursor->prev;
   }
}

//moveNext()
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L){//if cursr does not has space to move forward
   if (L->back == L->cursor){
      L->index = -1;
      L->cursor=NULL;
   }else{//if cursr has space to move forward
      L->index++;
      L->cursor = L->cursor->next;
   }
}

// prepend()
// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, int x){
   Node N = newNode(x);
   if( L==NULL ){
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   
   if(isEmpty(L)){//if list is empty make new item front and back item
      L->front = L->back = N;
   }else{//if list isnt empty add item to back
      L->front->prev = N; 
      N->next = L->front;
      L->front = N; 
   }
   L->length++;
   L->index++;
}

// append()
// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, int x){
   Node N = newNode(x);

   if( L==NULL ){
      printf("List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   
   if(isEmpty(L)){//if list is empty make new item front and back item
      L->front = L->back = N; 
   }else{ //if list isnt empty add item to back
      L->back->next = N;
      N->prev = L->back;
      L->back = N; 
   }
   L->length++;
}

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int x){
   if(isEmpty(L)){
      printf("List Error: calling insertBefore() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if(L->index<0){
      printf("List Error: calling insertBefore() while index is %d\n",L->index);
      exit(EXIT_FAILURE);
   }
   Node N = newNode(x);
   N->next = L->cursor;
   N->prev = L->cursor->prev;
   L->cursor->prev = N;
   if(N->prev==NULL){//if inserting at front of list
      L->front=N;
   }else{//if inserting not at front of list
   N->prev->next = N;
   }
   L->index++;
   L->length++;
}

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int x){
   Node N = newNode(x);
   if(isEmpty(L)){
      printf("List Error: calling insertAfter() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if(L->index<0){
      printf("List Error: calling insertAfter() while index is %d\n",L->index);
      exit(EXIT_FAILURE);
   }
   N->prev = L->cursor;
   N->next = L->cursor->next;
   L->cursor->next = N;
   if (N->next==NULL){//if inserting at end of list
      L->back=N;
   }else{//if not inserting at the end of list
      N->next->prev = N;
   }
   L->length++;
}

// deleteFront()
// Delete the front element. 
// Pre: length()>0
void deleteFront(List L){
   if(isEmpty(L)){
      printf("List Error: calling deleteFront on an empty List\n");
      exit(EXIT_FAILURE);
   }

   Node N = NULL;
   N = L->front;
   if (L->cursor==L->front){//if cursor as on to be deleted element
      L->cursor=NULL;
      L->index=0;
   }
   if( length(L)>1 ){//if list length is 1
      L->front = L->front->next; 
   }else{//normal operation
      L->front = L->back = NULL; 
      L->cursor=NULL;
      L->index=0;
   }
   L->index--;
   L->length--;
   freeNode(&N);
   N = NULL;
}

// deleteBack()
// Delete the back element. 
// Pre: length()>0
void deleteBack(List L){
   if(isEmpty(L)){
      printf("List Error: calling deleteBack on an empty List\n");
      exit(EXIT_FAILURE);
   }
   
   Node N = NULL;
   N = L->back;
   if (L->cursor==L->back){//if cursor as on to be deleted element
      L->cursor=NULL;
      L->index=-1;
   }
   if( length(L)>1 ){//if length is 1
      L->back = L->back->prev;
      L->back->next=NULL;
   }else{//normal operation
      L->front = L->back = NULL; 
      L->cursor=NULL;
      L->index=-1;
   }
   L->length--;
   freeNode(&N);
   N = NULL;
}

// delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
   if(isEmpty(L)){
      printf("List Error: calling delete() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if(L->index<0){
      printf("List Error: calling delete() while index is %d\n",L->index);
      exit(EXIT_FAILURE);
   }
   
   Node N = NULL;
   N = L->cursor;
   if(L->front==L->back){//if deleting last node in a list
      L->back = L->front = NULL;
      L->length--;
      freeNode(&N);
   }else if(L->cursor==L->front){//if deleting front
      deleteFront(L);
   }else if(L->cursor==L->back){//if deleting back
      deleteBack(L);
   }else{//normal operation
      L->cursor->prev->next = L->cursor->next;
      L->cursor->next->prev = L->cursor->prev;
      L->length--;
      freeNode(&N);
   }
   L->cursor = NULL;
   L->index = -1;
}

// Other Functions ------------------------------------------------------------

// printList()
// Prints a string representation of L consisting of a space separated list 
// of ints to stdout.
void printList(FILE* out, List L){
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   for(N = L->front; N != NULL; N = N->next){
      if(N->next == NULL){
         fprintf(out,"%d", N->data);
      }else{
         fprintf(out,"%d ", N->data);
      }
   }
}

// copyList()
// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L){
   Node N = NULL;
   List R = newList();
   for(N = L->front; N != NULL; N = N->next){
      append(R,N->data);
   }
   return(R);
}