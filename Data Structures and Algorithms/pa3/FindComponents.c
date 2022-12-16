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
#include"List.h"
#include"Graph.h"

int main(int argc, char * argv[]){

   //initilization
   FILE *in, *out;
   int u,v;

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
   fscanf(in,"%d",&u);
   Graph G = newGraph(u);
   List S = newList();
   for (int i = 1;getOrder(G)>=i;i++){
        append(S,i);
   }

   //read and add edges from file, break when 0 0 read
   while(true){
      fscanf(in,"%d %d",&u,&v);
      if((u==0) && (v==0)){
         break;
      }
      addArc(G,u,v);
   }

   //print out graph to file
   fprintf(out,"Adjacency list representation of G:\n");


   //read, solve, and print all Pathing questions
   List L = newList();
   while(true){
      fscanf(in,"%d %d",&u,&v);
      if((u==0) && (v==0)){
         break;
      }
   }
   printGraph(out,G);
   int SCC = 0;
   DFS(G,S);
   Graph T = transpose(G);
   DFS(T,S);
   for (moveBack(S);index(S)!=-1;movePrev(S)){
      if (getParent(T,get(S))==NIL){
         SCC++;
      }
   }

   fprintf(out,"\nG contains %d strongly connected components:",SCC);

   moveBack(S);
   int i = 0;
   List D = newList();
   for (moveBack(S);index(S)!=-1;movePrev(S)){
      prepend(D,get(S));
      if (getParent(T,get(S))==NIL){
         i++;
         fprintf(out,"\nComponent %d: ",i);
         printList(out,D);
         clear(D);
      }
   }

   // close files 
   fclose(in);
   fclose(out);

   //free memory
   freeGraph(&G);
   freeGraph(&T);
   freeList(&L);
   freeList(&D);

   return(0);
}
