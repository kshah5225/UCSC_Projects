/* Kunal Shah kgshah@ucsc.edu
 * File:   rpn.c
 * Author: kgshah
 *
 * Created on January 24, 2022, 11:54 AM
 */

#include "BOARD.h"
#include "stack.h"
#include "rpn.h"
#include "string.h"
#include "ctype.h"

int RPN_Evaluate(char * rpn_string, double * result){//RPN calculator is a function that simulates a Reverse Polish calculator as best as possible
    struct Stack stack = {};
    StackInit(&stack);
    char *token;
    char opp;
    double operand1;
    double operand2;
    if (strlen(rpn_string)>60){
        return INPUT_TOO_LONG;
    }
    token = strtok(rpn_string, " ");
    while(token != NULL){
        //printf( "token no:%s\n", token);
        if (strcmp(token,"+") == 0 || strcmp(token,"-") == 0 || strcmp(token,"*") == 0 || strcmp(token,"/") == 0){
            opp = *token;
            //printf("above is an operator\n");
            if (StackPop(&stack,&operand1) == STANDARD_ERROR){
                return RPN_ERROR_STACK_UNDERFLOW;
            }
            if (StackPop(&stack,&operand2) == STANDARD_ERROR){
                return RPN_ERROR_STACK_UNDERFLOW;
            }
            if (strcmp(token,"+") == 0){
                *result = operand2+operand1;
                //printf("\ndoes read plus:%f\n",result);
            }
            if (strcmp(token,"-") == 0){
                *result = operand2-operand1;
            }
            if (strcmp(token,"*") == 0){
                *result = operand2*operand1;
            }
            if (strcmp(token,"/") == 0){
                if (operand1 == 0){
                    return RPN_ERROR_DIVIDE_BY_ZERO;
                }
                *result = operand2/operand1;
            }
            if (StackPush(&stack,*result) == STANDARD_ERROR){
                return RPN_ERROR_STACK_OVERFLOW;
            }
        }else{
            if (!isdigit(*token)){
                return RPN_ERROR_INVALID_TOKEN;
            }
            //printf("%f is an number\n",atof(token));
            if (StackPush(&stack, atof(token)) == STANDARD_ERROR){
                return RPN_ERROR_STACK_OVERFLOW;
            }
            /*printf("{");
            for(int i=0; i<stack.currentItemIndex+1; i++) {
                printf("%f,", stack.stackItems[i]);
            }
            printf("}\n");*/
        }
        token = strtok(NULL, " ");
   }
    if (StackGetSize(&stack)==0){
        return RPN_ERROR_TOO_FEW_ITEMS_REMAIN;
    }
    if (StackGetSize(&stack)>1){
        return RPN_ERROR_TOO_MANY_ITEMS_REMAIN;
    }
    if (StackGetSize(&stack)==1){
        return RPN_NO_ERROR;
    }
}

int ProcessBackspaces(char *rpn_sentence){//this function should process back spaces using \b as an indicator that a backspace is occuring
    int rcnt = strlen(rpn_sentence);
    int iterator = -1;
    int wr_ite = -1;
    char new_str[strlen(rpn_sentence)];
    while(iterator<rcnt+1){
        iterator = iterator + 1;
        wr_ite = wr_ite + 1;
        if (rpn_sentence[iterator] == '\b'){
            wr_ite = wr_ite - 2;
        }else{
            rpn_sentence[wr_ite] = rpn_sentence[iterator];
        }
    }
    //printf("end");  
    //rpn_sentence[wr_ite+1] = NULL;
    return strlen(rpn_sentence);
}
