/* Kunal Shah kgshah@ucsc.edu
 * File:   stack.c
 * Author: kgshah
 *
 * Created on January 24, 2022, 11:54 AM
 */

#include "BOARD.h"
#include "stack.h"

void StackInit(struct Stack *stack){//stack init function
    stack->currentItemIndex = -1;
    stack->initialized = TRUE;
}

int StackPush(struct Stack *stack, double value){//stack push function takes in a value and adds it to pointed to stack and returns errors
    if (stack->currentItemIndex == STACK_SIZE-1){
        return STANDARD_ERROR;
    }
    if (stack->initialized != TRUE){
        return STANDARD_ERROR;
    }
    stack->currentItemIndex = stack->currentItemIndex +1;
    stack->stackItems[stack->currentItemIndex] = value;
    return SUCCESS;
}

int StackPop(struct Stack *stack, double *value){//stackpop function takes in a stack pointer and takes off the top value and feeds into the value pointer as well as returning error
    if (stack->currentItemIndex == -1){
        return STANDARD_ERROR;
    }
    if (stack->initialized != TRUE){
        return STANDARD_ERROR;
    }
    *value = stack->stackItems[stack->currentItemIndex];
    stack->currentItemIndex = stack->currentItemIndex - 1;
    return SUCCESS;
}

int StackIsEmpty(const struct Stack *stack){//returns whether the stack is or is not empty
    if (stack->initialized != TRUE){
        return FALSE;
    }
    if (stack->currentItemIndex == -1){
        return TRUE;
    }else{
        return FALSE;
    }
}

int StackIsFull(const struct Stack *stack){//returns whether the stack is or is not full
    if (stack->initialized != TRUE){
        return FALSE;
    }
    if (stack->currentItemIndex == STACK_SIZE - 1){
        return TRUE;
    }else{
        return FALSE;
    }
}

int StackGetSize(const struct Stack *stack){//Returns Stack size or size error of pointed to stack
    if (stack->initialized != TRUE){
        return SIZE_ERROR;
    }
    return stack->currentItemIndex + 1;
}