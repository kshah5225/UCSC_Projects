/* 
 * File:   Negotiation.c
 * Author: kgshah
 *
 * Created on March 9, 2022, 12:49 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Negotiation.h"

NegotiationData NegotiationHash(NegotiationData secret){
    return (secret * secret)%PUBLIC_KEY;
}

int NegotiationVerify(NegotiationData secret, NegotiationData commitment){
    /*if (((secret * secret)%PUBLIC_KEY)==commitment){
        return 1;
    }else{
        return 0;
    }*/
    return ((((secret * secret)%PUBLIC_KEY)==commitment));
}

NegotiationOutcome NegotiateCoinFlip(NegotiationData A, NegotiationData B){
    int matches = 0;
    for(int i = 0;i < 16;i++){
        if (((A>>i)&1) != ((B>>i)&1)){
            matches++;
        }
    }
    if (matches==1 || matches==3 || matches==5 || matches==7|| matches==9|| matches==11|| matches==13|| matches==15){
        return HEADS;
    }else{
        return TAILS;
    }
}

