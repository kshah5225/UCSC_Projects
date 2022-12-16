/* Kunal Shah kgshah@ucsc.edu
 * File:   ButtonsTest.c
 * Author: kgshah
 *
 * Created on February 8, 2022, 11:00 AM
 */

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "Buttons.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****

// **** Define global, module-level, or external variables here ****

// **** Declare function prototypes ****

int main(void)
{
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    T1CON = 0; // everything should be off
    T1CONbits.TCKPS = 2; // 1:64 prescaler
    PR1 = 0xFFFF; // interrupt at max interval
    T1CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T1IF = 0; //clear the interrupt flag before configuring
    IPC1bits.T1IP = 4; // priority of  4
    IPC1bits.T1IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T1IE = 1; // turn the interrupt on

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    printf("Welcome to kgshah's lab6 part4 (ButtonsTest).  Compiled on %s %s.\n", __TIME__, __DATE__);
    ButtonsInit();
    printf("Please press some buttons!\n");
    uint8_t FiBM = 3;//2,1st button mask
    uint8_t SeBM = 12;//3,4nd button mask
    uint8_t ThBM = 48;//5,6rd button mask
    uint8_t FoBM = 192;//7,8th button mask
    while(1){
        int CIBE = ButtonsCheckEvents();
        if (CIBE!=0){//if button states update print what update has occured
            printf("\nEVENT: ");//one update event per line
            if ((CIBE&FoBM) == 128){
                printf("4:DOWN");
            }else if((CIBE&FoBM) == 64){
                printf("4:  UP");
            }else{
                printf("4:----");
            }
            if ((CIBE&ThBM) == 32){
                printf("4:DOWN");
            }else if((CIBE&ThBM) == 16){
                printf("4:  UP");
            }else{
                printf("4:----");
            }
            if ((CIBE&SeBM) == 8){
                printf("4:DOWN");
            }else if((CIBE&SeBM) == 4){
                printf("4:  UP");
            }else{
                printf("4:----");
            }
            if ((CIBE&FiBM) == 2){
                printf("4:DOWN");
            }else if((CIBE&FiBM) == 1){
                printf("4:  UP");
            }else{
                printf("4:----");
            }
        }
    }
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

    while (1);
}

/**
 * This is the interrupt for the Timer1 peripheral. It should check for button events and stores them in a
 * module-level variable.
 * 
 * You should not modify this function for ButtonsTest.c or bounce_buttons.c!
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}