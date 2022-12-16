//-----------------------------------------------------------------------------
// ListClient.c
// Test client for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
   
   List A = newList();
   List B = newList();
   List C = newList();
   int X[] = {456,167,275,380,4,935,6,7,8,964,166,141,12,163,184,615,16,617,187,189,990};
   int i, u=-9, v=-3, w=-6; 
   bool equal = false;

   // initialize Lists A and B
   for(i=1; i<=20; i++){
      append(A, &X[i]);
      prepend(B, &X[i]);
      prepend(A, &X[i]);
   }

   // print both lists of integers in forward direction
   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   for(moveFront(B); index(B)>=0; moveNext(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");

   // print both lists of integers in backward direction
   for(moveBack(A); index(A)>=0; movePrev(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");

   // make a shallow copy of A
   moveFront(A);
   while( index(A)>=0 ){
      append(C, get(A));
      moveNext(A);
   }
   // print the copy in forward direction
   for(moveFront(C); index(C)>=0; moveNext(C)){
      printf("%d ", *(int*)get(C));
   }
   printf("\n");

   // check shallow equality of A and C by comparing pointers
   equal = (length(A)==length(C));
   moveFront(A);
   moveFront(C);
   while( index(A)>=0 && equal){
      equal = ( get(A)==get(C) );
      moveNext(A);
      moveNext(C);
   }
   printf("A equals C is %s\n", (equal?"true":"false") );

   printf("length(A)=%d\n", length(A));
   
   moveFront(A);
   for(i=0; i<5; i++) moveNext(A);     // at index 5
   printf("index(A)=%d\n", index(A));
   printf("get(A)=%d\n", *(int*)get(A));
   insertBefore(A, &u);                // now at index 6
   printf("index(A)=%d\n", index(A));
   printf("get(A)=%d\n", *(int*)get(A));
   for(i=0; i<9; i++) moveNext(A);     // at index 15
   printf("index(A)=%d\n", index(A));
   printf("get(A)=%d\n", *(int*)get(A));
   insertAfter(A, &v);                 // doesn't change index
   printf("index(A)=%d\n", index(A));
   printf("get(A)=%d\n", *(int*)get(A));
   for(i=0; i<5; i++) movePrev(A);     // at index 10
   printf("index(A)=%d\n", index(A));
   printf("get(A)=%d\n", *(int*)get(A));
   delete(A);                          // index is now undefined
   moveFront(A);
   printf("index(A)=%d\n", index(A));
   printf("get(A)=%d\n", *(int*)get(A));
   moveBack(A);                        // now at index 20
   printf("index(A)=%d\n", index(A));
   printf("get(A)=%d\n", *(int*)get(A));
   for(i=0; i<10; i++) movePrev(A);    // at index 10
   printf("index(A)=%d\n", index(A));
   printf("get(A)=%d\n", *(int*)get(A));
   set(A, &w);
   set(A, &u);

   // print A in forward and backward direction
   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   for(moveBack(A); index(A)>=0; movePrev(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");

   // check length of A, before and after clear()
   printf("%d\n", length(A));
   clear(A);
   printf("%d\n", length(A));

   freeList(&A);
   freeList(&B);
   freeList(&C);

   return(0);
}

/*
Output of this program:
990 189 187 617 16 615 184 163 12 141 166 964 8 7 6 935 4 380 275 167 167 275 380 4 935 6 7 8 964 166 141 12 163 184 615 16 617 187 189 990 
990 189 187 617 16 615 184 163 12 141 166 964 8 7 6 935 4 380 275 167 
990 189 187 617 16 615 184 163 12 141 166 964 8 7 6 935 4 380 275 167 167 275 380 4 935 6 7 8 964 166 141 12 163 184 615 16 617 187 189 990 
167 275 380 4 935 6 7 8 964 166 141 12 163 184 615 16 617 187 189 990 
990 189 187 617 16 615 184 163 12 141 166 964 8 7 6 935 4 380 275 167 167 275 380 4 935 6 7 8 964 166 141 12 163 184 615 16 617 187 189 990 
A equals C is true
length(A)=40
index(A)=5
get(A)=615
index(A)=6
get(A)=615
index(A)=15
get(A)=6
index(A)=15
get(A)=6
index(A)=10
get(A)=141
index(A)=0
get(A)=990
index(A)=40
get(A)=990
index(A)=30
get(A)=166
990 189 187 617 16 -9 615 184 163 12 166 964 8 7 6 -3 935 4 380 275 167 167 275 380 4 935 6 7 8 964 -6 141 12 163 184 615 16 617 187 189 990 
990 189 187 617 16 615 184 163 12 141 -6 964 8 7 6 935 4 380 275 167 167 275 380 4 935 -3 6 7 8 964 166 12 163 184 615 -9 16 617 187 189 990 
41
0
bash-4.2$ make ListTest
gcc -std=c17 -Wall -c ListTest.c
gcc -std=c17 -Wall -o ListTest ListTest.o List.o
bash-4.2$ ./ListTest
990 189 187 617 16 615 184 163 12 141 166 964 8 7 6 935 4 380 275 167 167 275 380 4 935 6 7 8 964 166 141 12 163 184 615 16 617 187 189 990 
990 189 187 617 16 615 184 163 12 141 166 964 8 7 6 935 4 380 275 167 
990 189 187 617 16 615 184 163 12 141 166 964 8 7 6 935 4 380 275 167 167 275 380 4 935 6 7 8 964 166 141 12 163 184 615 16 617 187 189 990 
167 275 380 4 935 6 7 8 964 166 141 12 163 184 615 16 617 187 189 990 
990 189 187 617 16 615 184 163 12 141 166 964 8 7 6 935 4 380 275 167 167 275 380 4 935 6 7 8 964 166 141 12 163 184 615 16 617 187 189 990 
A equals C is true
length(A)=40
index(A)=5
get(A)=615
index(A)=6
get(A)=615
index(A)=15
get(A)=6
index(A)=15
get(A)=6
index(A)=10
get(A)=141
index(A)=0
get(A)=990
index(A)=40
get(A)=990
index(A)=30
get(A)=166
990 189 187 617 16 -9 615 184 163 12 166 964 8 7 6 -3 935 4 380 275 167 167 275 380 4 935 6 7 8 964 -9 141 12 163 184 615 16 617 187 189 990 
990 189 187 617 16 615 184 163 12 141 -9 964 8 7 6 935 4 380 275 167 167 275 380 4 935 -3 6 7 8 964 166 12 163 184 615 -9 16 617 187 189 990 
41
0
*/