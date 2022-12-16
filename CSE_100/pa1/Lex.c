//-----------------------------------------------------------------------------
// Kunal Shah, kgshah
// 2022 Spring CSE101 PA1
// Lex.c
// Takes an input file and reorganizes the lines in alphabetical order and 
// places lines in an output file
//
// compile:
//
//     make Lex
//
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"List.h"

#define MAX_LINE_LEN 300

int main(int argc, char * argv[]){

   int line_count;
   FILE *in, *out;
   char line[MAX_LINE_LEN];

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
   line_count = 0;
   while( fgets(line, MAX_LINE_LEN, in) != NULL)  {
      line_count++;
   }

   //go back to start of the file
   fseek(in, 0, SEEK_SET);
   char* lines[line_count];

   //store all lines using malloc in a array of strings
   line_count = -1;
   while( fgets(line, MAX_LINE_LEN, in) != NULL)  {
      line_count++;
      lines[line_count] = malloc(strlen(line)+1);
      strcpy(lines[line_count], line);
   }
   line_count++;
   

   //goes through the list of strings and inserts them one by one via 
   //index into a linked list with its corresponding string index
   List A = newList();
   int element = 0;
   append(A,element);
   while(length(A)!=line_count){
      element++;
      moveBack(A);
      if(strcmp(lines[element],lines[back(A)])>=0){
         append(A,element);
      }else if(strcmp(lines[element],lines[front(A)])<=0){
         prepend(A,element);
      }else{
         while((strcmp(lines[element],lines[get(A)])<0)){
            movePrev(A);
            }
         insertAfter(A,element);
      }
   }

   //output strings to a file
   moveFront(A);
   for(int i=0;i<line_count;i++){
      fprintf(out,"%s", lines[get(A)]);
      moveNext(A);
   }

   
   // close files 
   fclose(in);
   fclose(out);

   //free memory
   moveFront(A);
   for(int i=0;i<line_count;i++){
      free(lines[get(A)]);
      moveNext(A);
   }
   clear(A);
   freeList(&A);

   return(0);
}