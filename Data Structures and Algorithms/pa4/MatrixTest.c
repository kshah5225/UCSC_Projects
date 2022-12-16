//-----------------------------------------------------------------------------
//  MatrixClient.c 
//  A test client for the Matrix ADT
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
     
int main(){
   int n=3;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   Matrix C, D, E, F, G, H, I, J, K;

   changeEntry(A, 1,1,1); changeEntry(B, 1,1,6);
   changeEntry(A, 1,2,2); changeEntry(B, 1,2,7);
   changeEntry(A, 1,3,3); changeEntry(B, 1,3,8);
   changeEntry(A, 2,1,8); changeEntry(B, 2,1,2);
   changeEntry(A, 2,2,5); changeEntry(B, 2,2,9);
   changeEntry(A, 2,3,6); changeEntry(B, 2,3,1);
   changeEntry(A, 3,1,4); changeEntry(B, 3,1,8);
   changeEntry(A, 3,2,3); changeEntry(B, 3,2,3);
   changeEntry(A, 3,3,9); changeEntry(B, 3,3,2);
   changeEntry(A, 3,3,0); changeEntry(B, 3,3,0);

   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);
   printf("\n");

   printf("%d\n", NNZ(B));
   printMatrix(stdout, B);
   printf("\n");

   C = scalarMult(1.5, A);
   printf("%d\n", NNZ(C));
   printMatrix(stdout, C);
   printf("\n");

   I = sum(A, A);
   printf("%d\n", NNZ(I));
   printMatrix(stdout, I);
   printf("\n");

   D = sum(A, B);
   printf("%d\n", NNZ(D));
   printMatrix(stdout, D);
   printf("\n");

   E = diff(A, A);
   printf("%d\n", NNZ(E));
   printMatrix(stdout, E);
   printf("\n");

   J = diff(B, A);
   printf("%d\n", NNZ(J));
   printMatrix(stdout, J);
   printf("\n");

   F = transpose(B);
   printf("%d\n", NNZ(F));
   printMatrix(stdout, F);
   printf("\n");

   G = product(B, B);
   printf("%d\n", NNZ(G));
   printMatrix(stdout, G);
   printf("\n");

   K = product(A, B);
   printf("%d\n", NNZ(K));
   printMatrix(stdout, K);
   printf("\n");

   H = copy(A);
   printf("%d\n", NNZ(H));
   printMatrix(stdout, H);
   printf("\n");

   printf("%s\n", equals(A, H)?"true":"false" );
   printf("%s\n", equals(A, B)?"true":"false" );
   printf("%s\n", equals(A, A)?"true":"false" );

   makeZero(A);
   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);

   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);
   freeMatrix(&I);
   freeMatrix(&J);
   freeMatrix(&K);

   return EXIT_SUCCESS;
}

/*
Output of this program:
8
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 8.0) (2, 5.0) (3, 6.0)
3: (1, 4.0) (2, 3.0)

8
1: (1, 6.0) (2, 7.0) (3, 8.0)
2: (1, 2.0) (2, 9.0) (3, 1.0)
3: (1, 8.0) (2, 3.0)

8
1: (1, 1.5) (2, 3.0) (3, 4.5)
2: (1, 12.0) (2, 7.5) (3, 9.0)
3: (1, 6.0) (2, 4.5)

8
1: (1, 2.0) (2, 4.0) (3, 6.0)
2: (1, 16.0) (2, 10.0) (3, 12.0)
3: (1, 8.0) (2, 6.0)

8
1: (1, 7.0) (2, 9.0) (3, 11.0)
2: (1, 10.0) (2, 14.0) (3, 7.0)
3: (1, 12.0) (2, 6.0)

0

7
1: (1, 5.0) (2, 5.0) (3, 5.0)
2: (1, -6.0) (2, 4.0) (3, -5.0)
3: (1, 4.0)

8
1: (1, 6.0) (2, 2.0) (3, 8.0)
2: (1, 7.0) (2, 9.0) (3, 3.0)
3: (1, 8.0) (2, 1.0)

9
1: (1, 114.0) (2, 129.0) (3, 55.0)
2: (1, 38.0) (2, 98.0) (3, 25.0)
3: (1, 54.0) (2, 83.0) (3, 67.0)

9
1: (1, 34.0) (2, 34.0) (3, 10.0)
2: (1, 106.0) (2, 119.0) (3, 69.0)
3: (1, 30.0) (2, 55.0) (3, 35.0)

8
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 8.0) (2, 5.0) (3, 6.0)
3: (1, 4.0) (2, 3.0)

true
false
true
0
*/