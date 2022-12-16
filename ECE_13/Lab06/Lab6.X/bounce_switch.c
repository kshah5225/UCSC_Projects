/* Kunal Shah kgshah@ucsc.edu
 * File:   bounce_switch.c
 * Author: kgshah
 *
 * Created on February 8, 2022, 11:00 AM
 */

// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>
					


//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
#include "Leds_Lab06.h"

// **** Declare any datatypes here ****
struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****
static struct Timer Timer1;
int direction = 0;
int sled = 1;
enum{
    Right = 1,
    Left
};
#define maxtime 1000
// **** Declare function prototypes ****


int main(void)
{
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    T1CON = 0; // everything should be off
    T1CONbits.TCKPS = 1; // 1:8 prescaler
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
    printf("Welcome to kgshah's lab6 part2 (bounce_switch).  Compiled on %s %s.\n",__TIME__,__DATE__);
    LEDS_INIT();
    LEDS_SET(sled);
    Timer1.timeRemaining = maxtime;
    Timer1.event = FALSE;
							 
	while(1){
        //poll timer events and react if any occur
        if (Timer1.event == TRUE){
            Timer1.event = FALSE;
            if (sled==1){//switches direction when led reaches left
                direction=Left;
            }
            if (sled==128){//switches direction when led reaches right
                direction=Right;
            }
            if(direction==Left){//itterates led to next one moving left
                sled = sled<<1;
            }
            if(direction==Right){//itterates led to next one moving right
                sled = sled>>1;
            }
            //printf("%d",sled);
            LEDS_SET(sled);//actual action of led being set
        }
    }			


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}


/**
 * This is the interrupt for the Timer1 peripheral. It will trigger at the frequency of the peripheral
 * clock, divided by the timer 1 prescaler and the interrupt interval.
 * 
 * It should not be called, and should communicate with main code only by using module-level variables.
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    //printf("state %d",SWITCH_STATES());
    Timer1.timeRemaining = Timer1.timeRemaining - (maxtime/(SWITCH_STATES()+1));//speed of led movement math
    if (Timer1.timeRemaining <= 0){
        Timer1.timeRemaining = maxtime;
        Timer1.event = TRUE;
    }
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/									
	 
}