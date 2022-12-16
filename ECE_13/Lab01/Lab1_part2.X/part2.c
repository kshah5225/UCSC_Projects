/* 
 * File:   part2.c
 * Author: kgshah
 *
 * Created on January 4, 2022, 11:54 AM
 */

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//Class specific libraries
#include "BOARD.h"


// User libraries
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    BOARD_Init();
    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/

    //Declare Variables
    double fahr, celsius,kelv;
    int lower, upper, step;

    //initialize Variables
    lower = 0; //lower limit of temperature
    upper = 300; //upper limit
    step = 20; //step size
    fahr = lower; //starting temp value set
    kelv = lower; //starting temp value set

    // Print out table
    printf("    F     C\n");
    while (fahr <= upper) {
        celsius = (5.00 / 9.00)*(fahr - 32.0);
        printf("%7.1f %04.0f\n", (double) fahr, (double) celsius);
        fahr = fahr + step;
    }
    
    printf("\n     K     F\n");
    while (kelv <= upper) {
        fahr = (((1.8)*(kelv - 273.15)) + 32.0);
        printf("%3.3f %5.6f\n", (double) kelv, (double) fahr);
        kelv = kelv + step;
    }

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks.
     **************************************************************************************************/

    // Returning from main() is bad form in embedded environments. So we sit and spin.
    while (1);
}
