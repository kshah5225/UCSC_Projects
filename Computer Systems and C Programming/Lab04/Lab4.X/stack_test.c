/* Kunal Shah kgshah@ucsc.edu
 * File:   stack_test.c
 * Author: kgshah
 *
 * Created on January 24, 2022, 11:54 AM
 */

// **** Include libraries here ****
// Standard libraries
#include "stdio.h"

//CMPE13 Support Library
#include "BOARD.h"


// User libraries
#include "stack.h"

int main()
{
    BOARD_Init();

    printf("\n###### Beginning kgshah's stack test harness: ####\n\n");

    //What follows is starter code.  You will need to modify it!
    
    printf("Does StackInit() set the currentItemIndex appropriately?\n");//current item index testing
    struct Stack stack = {};
    StackInit(&stack);
    if (stack.currentItemIndex == -1) {
        printf("passed\n");
    } else {
        printf("failed\n");
    }

    printf("Does StackInit() set the initialized appropriately?\n");//stack initialized testing
    if (stack.initialized == TRUE) {
        printf("passed\n");
    } else {
        printf("failed\n");
    }
    
    printf("Does StackPush() set increment appropriately?\n");//increment testing
    StackPush(&stack, 11);
    if (stack.currentItemIndex == 0) {
        printf("passed\n");
    } else {
        printf("failed\n");
    }
    
    printf("Does StackPush() add value to stack correctly?\n");//Stack Push testing
    if (stack.stackItems[0] == 11){
        printf("passed\n");
    } else {
        printf("failed\n");
    }
    
    printf("Does StackPop() add value var correctly?\n");//Stack Pop testing if correct value is given
    double tempvar;
    StackPop(&stack, &tempvar);
    if (tempvar == 11){
        printf("passed\n");
    } else {
        printf("failed\n");
    }
    
    printf("Does StackPop() remove value/change index correctly?\n");//Stack Pop testing if correct current item index shift is done
    if (stack.currentItemIndex == -1){
        printf("passed\n");
    } else {
        printf("failed\n");
    }
    
    printf("Does StackIsEmpty() detect empty stack correctly?\n");//StackisEmpty==TRUE testing
    if (StackIsEmpty(&stack) == TRUE){
        printf("passed\n");
    } else {
        printf("failed\n");
    }
    
    printf("Does StackIsEmpty() detect empty stack correctly?\n");//StackisEmpty==FALSE testing
    StackPush(&stack, 15);
    if (StackIsEmpty(&stack) == FALSE){
        printf("passed\n");
    } else {
        printf("failed\n");
    }
    
    printf("Does StackIsFull() detect a not full stack correctly?\n");//StackIsFull==FALSE testing
    StackPush(&stack, 15);
    if (StackIsFull(&stack) == FALSE){
        printf("passed\n");
    } else {
        printf("failed\n");
    }
    
    printf("Does StackIsFull() detect a full stack correctly?\n");//StackIsFull==TRUE testing
    StackPush(&stack, 15);
    StackPush(&stack, 15);
    StackPush(&stack, 15);
    StackPush(&stack, 15);
    StackPush(&stack, 15);
    StackPush(&stack, 15);
    StackPush(&stack, 15);
    StackPush(&stack, 15);
    StackPush(&stack, 15);
    StackPush(&stack, 15);
    StackPush(&stack, 15);
    StackPush(&stack, 15);
    StackPush(&stack, 15);
    StackPush(&stack, 15);
    StackPush(&stack, 15);
    StackPush(&stack, 15);
    StackPush(&stack, 15);
    StackPush(&stack, 15);
    StackPush(&stack, 15);
    StackPush(&stack, 15);
    if (StackIsFull(&stack) == TRUE){
        printf("passed\n");
    } else {
        printf("failed\n");
    }
    
    printf("Does StackGetSize() detect a stack size correctly?\n");//StackGetSize() testing
    StackPop(&stack, &tempvar);
    StackPop(&stack, &tempvar);
    StackPop(&stack, &tempvar);
    StackPop(&stack, &tempvar);
    if (StackGetSize(&stack) == 16){
        printf("passed\n");
    } else {
        printf("failed\n");
    }
    
    BOARD_End();
    //test stackInit:
    while (1);
    return 0;
}


