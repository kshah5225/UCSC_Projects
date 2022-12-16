/* Kunal Shah kgshah@ucsc.edu
 * File:   bounce_buttons.c
 * Author: kgshah
 *
 * Created on February 8, 2022, 11:00 AM
 */

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
#include "Buttons.h"
#include "Leds_Lab06.h"

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****
struct Timer {
    uint8_t event;
};
// **** Define global, module-level, or external variables here ****
int MBCE;
static struct Timer timer1;
#define DLED 0xC0//LED groupings
#define CLED 0x30
#define BLED 0x0C
#define ALED 0x03
#define S1M 1//Switch masks
#define S2M 2
#define S3M 4
#define S4M 8
#define B1M 3
#define B2M 12
#define B3M 48
#define B4M 192

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
    printf("Welcome to kgshah's lab6 part5 (bounce_buttons).  Compiled on %s %s.\n", __TIME__, __DATE__);
    ButtonsInit();//init button pins
    LEDS_INIT();//led button pins
    while(1){
        if (timer1.event == TRUE){//check if new button event has happened
            timer1.event = FALSE;
            int MSS = SWITCH_STATES();
            int MSS1 = MSS&&S1M;//separate bits corresponding to each switch
            int MSS2 = MSS&&S2M;
            int MSS3 = MSS&&S3M;
            int MSS4 = MSS&&S4M;
            int MBCE1 = MBCE&B1M;
            int MBCE2 = MBCE&B2M;
            int MBCE3 = MBCE&B3M;
            int MBCE4 = MBCE&B4M;
            if (MBCE4 == BUTTON_EVENT_4DOWN && MSS4==FALSE){//if statements to determine which LEDS need to be flipped
                LEDS_SET(LEDS_GET()^DLED);
            }
            if (MBCE4 == BUTTON_EVENT_4UP && MSS4==TRUE){
                LEDS_SET(LEDS_GET()^DLED);
            }
            if (MBCE3 == BUTTON_EVENT_3DOWN && MSS3==FALSE){
                LEDS_SET(LEDS_GET()^CLED);
            }
            if (MBCE3 == BUTTON_EVENT_3UP && MSS3==TRUE){
                LEDS_SET(LEDS_GET()^CLED);
            }
            if (MBCE2 == BUTTON_EVENT_2DOWN && MSS2==FALSE){
                LEDS_SET(LEDS_GET()^BLED);
            }
            if (MBCE2 == BUTTON_EVENT_2UP && MSS2==TRUE){
                LEDS_SET(LEDS_GET()^BLED);
            }
            if (MBCE1 == BUTTON_EVENT_1DOWN && MSS1==FALSE){
                LEDS_SET(LEDS_GET()^ALED);
            }
            if (MBCE1 == BUTTON_EVENT_1UP && MSS1==TRUE){
                LEDS_SET(LEDS_GET()^ALED);
            }
            //printf("%d",SWITCH_STATES());
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
    MBCE = ButtonsCheckEvents();//check for updated buttons
    if (MBCE!=0){//check if buttons were updated or not
        timer1.event = TRUE;
    }

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}