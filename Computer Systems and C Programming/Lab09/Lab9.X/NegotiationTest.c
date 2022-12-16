/* 
 * File:   NegotiationTest.c
 * Author: kshah
 *
 * Created on March 8, 2022, 5:32 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Negotiation.h"

/*
 * 
 */
int main(int argc, char** argv) {
    printf("-----This is the Negotiation Tester-----\n");
    if (NegotiationHash(3)==9){
        printf("CORRECT:NegotiationHash(3) == 9\n");
    }else{
        printf("INCORRECT:NegotiationHash(3) == 9\n"); 
    }
    if (NegotiationHash(12345) == 43182){
        printf("CORRECT:NegotiationHash(12345) == 43182\n");
    }else{
        printf("INCORRECT:NegotiationHash(12345) == 43182\n"); 
    }
    
    if (NegotiationVerify(43182,12345) == 0){
        printf("CORRECT:NegotiationVerify(43182,12345) == FALSE\n");
    }else{
        printf("INCORRECT:NegotiationVerify(43182,12345) == FALSE\n");
    }
    if (NegotiationVerify(12345,43182) == 1){
        printf("CORRECT:NegotiationVerify(12345,43182) == TRUE\n");
    }else{
        printf("INCORRECT:NegotiationVerify(12345,43182) == TRUE\n");
    }
    
    if (NegotiateCoinFlip(1,2)==1){
        printf("CORRECT:NegotiateCoinFlip(1,2) == TAILS\n");
    }else{
        printf("INCORRECT:NegotiateCoinFlip(1,2) == TAILS\n");
    }
    if (NegotiateCoinFlip(3,2)==0){
        printf("CORRECT:NegotiateCoinFlip(3,2) == HEADS\n");
    }else{
        printf("INCORRECT:NegotiateCoinFlip(3,2) == HEADS\n");
    }
    if (NegotiateCoinFlip(3,2+0xBEEF)==0){
        printf("CORRECT:NegotiateCoinFlip(3,2+0xBEEF) == HEADS\n");
    }else{
        printf("INCORRECT:NegotiateCoinFlip(3,2+0xBEEF) == HEADS\n");
    }
    if (NegotiateCoinFlip(1,1)==1){
        printf("CORRECT:NegotiateCoinFlip(1,1) == TAILS\n");
    }else{
        printf("INCORRECT:NegotiateCoinFlip(1,1) == TAILS\n");
    }
    return (EXIT_SUCCESS);
}

