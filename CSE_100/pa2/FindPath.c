//-----------------------------------------------------------------------------
// Kunal Shah, kgshah
// 2022 Spring CSE101 PA2
// Lex.c
// Takes an input file and finds the shortest Path
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

   //read and add edges from file, break when 0 0 read
   while(true){
      fscanf(in,"%d %d",&u,&v);
      if((u==0) && (v==0)){
         break;
      }
      addEdge(G,u,v);
   }

   //print out graph to file
   printGraph(out,G);

   //read, solve, and print all Pathing questions
   List L = newList();
   while(true){
      fscanf(in,"%d %d",&u,&v);
      if((u==0) && (v==0)){
         break;
      }
      BFS(G,u);
      getPath(L,G,v);
      if((back(L)-1) == INF){
         fprintf(out,"\n\nThe distance from %d to %d is infinity\nNo %d-%d path exists",u,v,u,v);
      }else{
         fprintf(out,"\n\nThe distance from %d to %d is %d\nA shortest %d-%d path is:",u,v,length(L)-1,u,v);
         printList(out,L);
      }
      clear(L);
   }
   fprintf(out,"\n");



   // close files 
   fclose(in);
   fclose(out);

   //free memory
   freeGraph(&G);
   freeList(&L);

   return(0);
}
