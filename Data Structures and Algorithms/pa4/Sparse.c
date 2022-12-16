//-----------------------------------------------------------------------------
// Kunal Shah, kgshah
// 2022 Spring CSE101 PA3
// FindComponents.c
// Takes an input file and finds the shortest Path and well connected loops
//
// compile:
//
//     make
//
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"Matrix.h"

int main(int argc, char * argv[]){

   //initilization
   FILE *in, *out;
   int x,y,i,a,b;
   double d;

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   if( in==NULL ){
      printf("Unable to open input file %s for reading\n", argv[1]);
      exit(1);
   }
   out = fopen(argv[2], "w");
   if( out==NULL ){
      printf("Unable to open output file %s for writing\n", argv[2]);
      exit(1);
   }

   // read each line of input file and then count lines
   fscanf(in,"%d %d %d\n",&i,&a,&b);
   Matrix A = newMatrix(i);
   Matrix B = newMatrix(i);

   //read and add edges from file, break when 0 0 read
   while(a!=0){
      fscanf(in,"%d %d %lf",&x,&y,&d);
      changeEntry(A, x, y, d);
      a--;
   }
   fscanf(in,"\n");
   while(b!=0){
      fscanf(in,"%d %d %lf",&x,&y,&d);
      changeEntry(B, x, y, d);
      b--;
   }
   fprintf(out,"A has %d non-zero entries:\n",NNZ(A));
   printMatrix(out,A);
   fprintf(out,"\nB has %d non-zero entries:\n",NNZ(B));
   printMatrix(out,B);

   fprintf(out,"\n(1.5)*A =\n");
   Matrix C = scalarMult(1.5,A);
   printMatrix(out,C);
   freeMatrix(&C);

   fprintf(out,"\nA+B =\n");
   Matrix D = sum(A,B);
   printMatrix(out,D);
   freeMatrix(&D);

   fprintf(out,"\nA+A =\n");
   Matrix E = sum(A,A);
   printMatrix(out,E);
   freeMatrix(&E);
  
   fprintf(out,"\nB-A =\n");
   Matrix F = diff(B,A);
   printMatrix(out,F);
   freeMatrix(&F);

   fprintf(out,"\nA-A =\n");
   Matrix J = diff(A,A);
   printMatrix(out,J);
   freeMatrix(&J);
   
   fprintf(out,"\nTranspose(A) =\n");
   Matrix G = transpose(A);
   printMatrix(out,G);
   freeMatrix(&G);

   fprintf(out,"\nA*B =\n");
   Matrix H = product(A,B);
   printMatrix(out,H);
   freeMatrix(&H);

   fprintf(out,"\nB*B =\n");
   Matrix I = product(B,B);
   printMatrix(out,I);
   freeMatrix(&I);

   // close files 
   fclose(in);
   fclose(out);

   //free memory
   freeMatrix(&A);
   freeMatrix(&B);

   return(0);
}
