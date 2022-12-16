/* Kunal Shah kgshah@ucsc.edu
 * File:   Lab04_main.c
 * Author: kgshah
 *
 * Created on January 24, 2022, 11:54 AM
 */

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "rpn.h"

// **** Set macros and preprocessor directives ****
// The lab calls for 60 characters of user input
#define MAX_INPUT_LENGTH 60

int main() {
    BOARD_Init();

    //What follows is starter code.  You will need to modify it!

    char rpn_sentence[MAX_INPUT_LENGTH + 2];
    double result;
    int error;

    printf("\nWelcome to kgshah'S RPN calculator.  Compiled on %s %s", __DATE__, __TIME__);
    while (1) {

        printf("\nEnter floats and + - / * in RPN format:");

        //scanf("%[^\n]s", rpn_sentence);
        //scanf("%s", rpn_sentence);
        fgets(rpn_sentence, sizeof (rpn_sentence), stdin);//asks user for input in rpn format
        while ((getchar())!='\n');//prevents the double enter issue
        //rpn_sentence[strlen(rpn_sentence)-4] = '\0';
        
        char *token2;
        token2 = strtok(rpn_sentence, "\n");//gets rid of the garbage at the end of the string by abusing strtok())
        
        //printf("\n input: %s \n",token2);
        
        ProcessBackspaces(rpn_sentence);
        
        printf("Solving: %s \n",token2);

        error = RPN_Evaluate(rpn_sentence, &result);//running rpn calc
        
        if (error == RPN_NO_ERROR){//interpreting any error message or printing correct value if no error
            printf("result = %f\n", result);
        }else if(error == RPN_ERROR_STACK_OVERFLOW){
            printf("ERROR:Too many numbers to remember at once so try to use more operators or fewer numbers in one stretch");
        }else if(error == RPN_ERROR_STACK_UNDERFLOW){
            printf("ERROR:Not enough numbers to complete operations");
        }else if(error == RPN_ERROR_INVALID_TOKEN){
            printf("ERROR:Dont use any non numbers other than the 4 acceptable basic operations");
        }else if(error == RPN_ERROR_DIVIDE_BY_ZERO){
            printf("ERROR:Dont Divide by zero at any point");
        }else if(error == RPN_ERROR_TOO_FEW_ITEMS_REMAIN){
            printf("ERROR:There are not enough numbers to evaluate");
        }else if(error == RPN_ERROR_TOO_MANY_ITEMS_REMAIN){
            printf("ERROR:There are not enough operations leaving some numbers unused");
        }else if(error == INPUT_TOO_LONG){
            printf("ERROR:You cannot enter a string longer than 60 total characters, please shorten your calculation");
        }
    }

    while (1);
}
