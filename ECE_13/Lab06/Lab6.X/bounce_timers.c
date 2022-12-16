/* Kunal Shah kgshah@ucsc.edu
 * File:   bounce_timers.c
 * Author: kgshah
 *
 * Created on February 8, 2022, 11:00 AM
 */

// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>
#include <GenericTypeDefs.h>

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
static struct Timer timerA;
static struct Timer timerB;
static struct Timer timerC;
#define Hz 38//refresh rate
#define Atime 2//time per led toggle
#define Btime 3
#define Ctime 5
#define ALED 0x01//individual LED def
#define BLED 0x02
#define CLED 0x04
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
    printf("Welcome to kgshah's lab6 part1 (timers).  Compiled on %s %s.\n", __TIME__, __DATE__);
    
    LEDS_INIT();
    //LEDS_SET(0xFF);
    
    timerA.event = FALSE;//initial timer values
    timerA.timeRemaining = Atime*Hz;//essentially calcs secconds * processes per sec
    
    timerB.event = FALSE;
    timerB.timeRemaining = Btime*Hz;
    
    timerC.event = FALSE;
    timerC.timeRemaining = Ctime*Hz;
    
    while (1) {
        if (timerA.event == TRUE){//Know which event to trigger what actionset
            timerA.event = FALSE;//this is the 2 second timer by default
            printf("A");
            LEDS_SET(LEDS_GET()^ALED);
        }
        if (timerB.event == TRUE){
            timerB.event = FALSE;//this is the 3 second timer by default
            printf("B");
            LEDS_SET(LEDS_GET()^BLED);
        }
        if (timerC.event == TRUE){
            timerC.event = FALSE;//this is the 5 second timer by default
            printf("C");
            LEDS_SET(LEDS_GET()^CLED);
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
    
    timerA.timeRemaining--;//iterates timer down
    timerB.timeRemaining--;
    timerC.timeRemaining--;
    
    if (timerA.timeRemaining == 0){//checking if any timers hit 0
        timerA.timeRemaining = Atime*Hz;
    }
    
    if (timerB.timeRemaining == 0){//checking if any timers hit 0
        timerB.event = TRUE;
        timerB.timeRemaining = Btime*Hz;
    }
    
    if (timerC.timeRemaining == 0){//checking if any timers hit 0
        timerC.event = TRUE;
        timerC.timeRemaining = Ctime*Hz;
    }
    
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}