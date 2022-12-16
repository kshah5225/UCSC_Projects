//-----------------------------------------------------------------------------
// Kunal Shah, kgshah
// 2022 Spring CSE101 PA1
// ListTest.c
// A test client for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
   //initilizeing 2 lists
   List A = newList();
   List B = newList();

   //manipulating A list for 1st print line
   append(A,4);
   append(A,8);
   append(A,16);
   prepend(A,2);
   prepend(A,1);
   moveFront(A);
   moveNext(A);
   insertAfter(A,3);
   moveBack(A);
   movePrev(A);
   insertBefore(A,6);
   printf("A[%d] = {",length(A));
   printList(stdout,A);
   printf("}   %d %d %d %d %d %d\n",length(A),index(A),front(A),back(A),get(A),equals(A,B));

   //manipulating A list for 2nd print line
   deleteFront(A);
   deleteBack(A);
   movePrev(A);
   delete(A);
   moveBack(A);
   printf("A[%d] = {",length(A));
   printList(stdout,A);
   printf("}   %d %d %d %d %d %d\n",length(A),index(A),front(A),back(A),get(A),equals(A,B));

   //copying A List to C list for 3rd print line
   List C = copyList(A);
   moveFront(C);
   printf("C[%d] = {",length(C));
   printList(stdout,C);
   printf("}   %d %d %d %d %d %d\n",length(C),index(C),front(C),back(C),get(C),equals(C,A));

   //clearing C list for 4th line printout
   clear(C);
   printf("C[%d] = {",length(C));
   printList(stdout,C);
   printf("}   %d %d %d\n",length(C),index(C),equals(C,B));

   //manipulating A list for 5th print line
   append(A,16);
   append(A,32);
   append(A,64);
   append(A,48);
   moveBack(A);
   set(A,128);
   printf("A[%d] = {",length(A));
   printList(stdout,A);
   printf("}   %d %d %d %d %d %d\n",length(A),index(A),front(A),back(A),get(A),equals(A,B));

   //manually making B look like A expected output anc checking equal() in 6th line
   append(B,2);
   append(B,3);
   append(B,4);
   append(B,8);
   append(B,16);
   append(B,32);
   append(B,64);
   append(B,128);
   moveBack(B);
   printf("B[%d] = {",length(B));
   printList(stdout,B);
   printf("}   %d %d %d %d %d %d\n",length(B),index(B),front(B),back(B),get(B),equals(A,B));   

   //no printout but if segfault occurs or if valgrind memleak occurs the issue is likely here
   freeList(&A);
   freeList(&B);
   freeList(&C);

/* Expected Output:
A[7] = {1 2 3 4 6 8 16 }   7 5 1 16 8 0
A[4] = {2 3 4 8 }   4 3 2 8 8 0
C[4] = {2 3 4 8 }   4 0 2 8 2 1
C[0] = {}   0 -1 1
A[8] = {2 3 4 8 16 32 64 128 }   8 7 2 128 128 0
B[8] = {2 3 4 8 16 32 64 128 }   8 7 2 128 128 1
*/

   return(0);
}
