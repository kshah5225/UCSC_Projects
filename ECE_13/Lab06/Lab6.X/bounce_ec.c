/* Kunal Shah kgshah@ucsc.edu
 * File:   bounce_ec.c
 * Author: kgshah
 *
 * Created on February 8, 2022, 11:00 AM
 */

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "Oled.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
#include "Leds_Lab06.h"
#include "Buttons.h"

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****
struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};
struct AdcResult {//making timer struct
    uint8_t event;
    int16_t voltage;
};
// **** Define global, module-level, or external variables here ****
#define maxtime 1023
int unfroz = TRUE;
static struct Timer timer1;
int MBCE;
static struct Timer Timer1;
int direction = 0;
int sled = 1;
enum{
    Right = 1,
    Left
};
static struct AdcResult ADC1;//static to check for voltage leaving window
#define window 5
#define potmin 0
#define potmax 1023
#define clrB 0
#define B1M 3//button masks
#define B2M 12
#define B3M 48
#define B4M 192
#define S1M 1//Switch masks
#define S2M 2
#define S3M 4
#define S4M 8
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


    // Enable interrupts for the ADC
    IPC6bits.AD1IP = 2;
    IPC6bits.AD1IS = 0;
    IEC1bits.AD1IE = 1;

    // Set B2 to an input so AN2 can be used by the ADC.
    TRISBbits.TRISB2 = 1;

    // Configure and start the ADC
    AD1CHSbits.CH0SA = 2; // add B2 to the mux
    AD1PCFGbits.PCFG2 = 0; // add b2 to the ADC
    AD1CSSLbits.CSSL2 = 1; // and add b2 to the scanner

    AD1CON1 = 0; // start with 0
    AD1CON1bits.SSRC = 0b111; // auto conversion
    AD1CON1bits.ASAM = 1; // auto sample

    AD1CON2 = 0; // start with 0
    AD1CON2bits.SMPI = 7; // one interrupt per 8 samples

    AD1CON3 = 0; // start with 0
    AD1CON3bits.SAMC = 29; // long sample time
    AD1CON3bits.ADCS = 50; // long conversion time

    AD1CON1bits.ADON = 1; // and finally turn it on

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    printf("Welcome to kgshah's lab6 part6 (Extra Credit).  Compiled on %s %s.\n",__TIME__,__DATE__);
    LEDS_INIT();
    LEDS_SET(sled);
    Timer1.timeRemaining = maxtime;
    Timer1.event = FALSE;
    OledInit();//starting up the olde
    ADC1.voltage = ADC1BUF0;//initial pot reading
    ADC1.event = TRUE;//run event true for one initial run
    char str[45];//storage space for sprintf
	while(1){
        int MBCE1 = MBCE&B1M;
        int MBCE2 = MBCE&B2M;
        int MBCE3 = MBCE&B3M;
        int MBCE4 = MBCE&B4M;
        int MSS = SWITCH_STATES();
        int MSS1 = MSS&&S1M;//separate bits corresponding to each switch
        int MSS2 = MSS&&S2M;
        int MSS3 = MSS&&S3M;
        int MSS4 = MSS&&S4M;
        if (MBCE4 == BUTTON_EVENT_4DOWN && MSS4==FALSE){//if statements to determine which LEDS need to be flipped
            if (unfroz == TRUE){
                unfroz = FALSE;
            }else{
                unfroz = TRUE;
            }
        }
        if (MBCE4 == BUTTON_EVENT_4UP && MSS4==TRUE){
            if (unfroz == TRUE){
                unfroz = FALSE;
            }else{
                unfroz = TRUE;
            }
        }
        if (MBCE3 == BUTTON_EVENT_3DOWN && MSS3==FALSE){
            if (unfroz == TRUE){
                unfroz = FALSE;
            }else{
                unfroz = TRUE;
            }
        }
        if (MBCE3 == BUTTON_EVENT_3UP && MSS3==TRUE){
            if (unfroz == TRUE){
                unfroz = FALSE;
            }else{
                unfroz = TRUE;
            }
        }
        if (MBCE2 == BUTTON_EVENT_2DOWN && MSS2==FALSE){
            if (unfroz == TRUE){
                unfroz = FALSE;
            }else{
                unfroz = TRUE;
            }
        }
        if (MBCE2 == BUTTON_EVENT_2UP && MSS2==TRUE){
            if (unfroz == TRUE){
                unfroz = FALSE;
            }else{
                unfroz = TRUE;
            }
        }
        if (MBCE1 == BUTTON_EVENT_1DOWN && MSS1==FALSE){
            if (unfroz == TRUE){
                unfroz = FALSE;
            }else{
                unfroz = TRUE;
            }
        }
        if (MBCE1 == BUTTON_EVENT_1UP && MSS1==TRUE){
            if (unfroz == TRUE){
                unfroz = FALSE;
            }else{
                unfroz = TRUE;
            }
        }
        if (ADC1.event == TRUE){//when you need to put new value on oled
            OledClear(clrB);
            sprintf(str,"Potentiometer value:\n %d\n %d%%",ADC1.voltage,(ADC1.voltage*100)/1023);
            printf("%s",str);
            OledDrawString(str);
            OledUpdate();
        }
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

    while (1);
}

/**
 * This is the interrupt for the Timer1 peripheral.
 */
void __ISR(_TIMER_1_VECTOR, IPL4AUTO) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;
    //printf("state %d",SWITCH_STATES());
    Timer1.timeRemaining = Timer1.timeRemaining - (((ADC1.voltage+1))*unfroz);//speed of led movement math
    if (Timer1.timeRemaining <= 0){
        Timer1.timeRemaining = maxtime;
        Timer1.event = TRUE;
    }
    MBCE = ButtonsCheckEvents();//check for updated buttons
    if (MBCE!=0){//check if buttons were updated or not
        timer1.event = TRUE;
    }
}

/**
 * This is the ISR for the ADC1 peripheral.
 */
void __ISR(_ADC_VECTOR, IPL2AUTO) AdcHandler(void)
{
    // Clear the interrupt flag.
    IFS1bits.AD1IF = 0;//This section of code checks if avg pot value is not outside of the old value's window
    int ADCAVG = (ADC1BUF0 + ADC1BUF1 + ADC1BUF2 + ADC1BUF3 + ADC1BUF4 + ADC1BUF5 + ADC1BUF6 + ADC1BUF7)/8;
    if (ADCAVG > ADC1.voltage + window || ADCAVG < ADC1.voltage - window){
        ADC1.event = TRUE;//telling the oled update part of code to run
        if (ADCAVG<=window){//these if statements are for pot edge handling
            ADC1.voltage = potmin;
        }else if ( ADCAVG>= (potmax-window)){
            ADC1.voltage = potmax;
        }else{
            ADC1.voltage = ADCAVG;
        }
    }
}