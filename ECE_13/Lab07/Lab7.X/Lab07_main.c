// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CSE13E Support Library
#include "BOARD.h"
#include "Ascii.h"
#include "Buttons.h"
#include "Oled.h"
#include "Adc.h"
// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>
// User libraries
#include "Leds.h"


// **** Set any macros or preprocessor directives here ****
// Set a macro for resetting the timer, makes the code a little clearer.
#define TIMER_2HZ_RESET() (TMR1 = 0)


// **** Set any local typedefs here ****
typedef enum {
    SETUP, SELECTOR_CHANGE_PENDING, COOKING, RESET_PENDING//enum for states
} OvenState;
typedef enum {
    BAKE, TOAST, BROIL//enum for different oven modes
} OvenMode;
typedef enum {
    TEMP, TIME//enum for decideing what is being edited with >
} Editing;

typedef struct {//all data pretaining to what needs to be displayed and manipulated
    OvenState state;
    OvenMode mode;
    uint16_t time;
    uint16_t totaltime;
    uint16_t temperature;
    Editing editing;
    uint8_t flashes;
    uint8_t LEDS;
    //add more members to this struct
} OvenData;
typedef struct {//backend update variables
    uint8_t ADC_CHANGED;
    uint8_t Btn3Down;
    uint8_t Btn4Down;
    uint8_t Btn3L;
    uint8_t Btn3S;
    uint8_t Btn4L;
    uint16_t Btn3press_time;
    uint16_t Btn4press_time;
    #define noLEDSON 0x00
#define oneLEDSON 0x80
#define twoLEDSON 0xC0
#define threeLEDSON 0xE0
#define fourLEDSON 0xF0
#define fiveLEDSON 0xF8
#define sixLEDSON 0xFC
#define sevenLEDSON 0xFE
#define eightLEDSON 0xFF
#define TotalLEDS 8
#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define EIGHT 8
#define NINE 9
#define TEN 10
#define LCD_STRING_SIZE 200
#define SECperMIN 60
#define POTSLOPE 0.2493
#define temp_offset 300
#define time_offset 1
#define defaulttemp 350

    //add more members to this struct
} OvenEvents;

// **** Declare any datatypes here ****
//all data pretaining to what needs to be displayed and manipulated (BELOW))
static OvenData ovenData = {SETUP,BAKE,ONE,ONE,defaulttemp,TIME,EIGHT,ZERO};
static OvenEvents ovenEvents = {FALSE,FALSE,FALSE,FALSE,FALSE,0};//backend update variables
static uint16_t TIMER_TICK = 0;//keep up time
// **** Define any module-level, global, or external variables here ****


// **** Put any helper functions here ****


/*This function will update your OLED to reflect the state .*/
void updateOvenOLED(OvenData ovenData){
    OledClear(OLED_COLOR_BLACK);
    char topovenstr[EIGHT];//char arrays to hold print data
    char botovenstr[EIGHT];
    char ovenstr[LCD_STRING_SIZE];
    char timestr[EIGHT];
    //if (TIMER_TICK<2){//? does timer have to default to 0.01
    //    ovenData.time = 1;
    //}
    if ((ovenData.time%SECperMIN) < TEN){//time print data
        sprintf(timestr," %d"":0""%d", (int)(ovenData.time/SECperMIN), (ovenData.time%SECperMIN));
    }else{
        sprintf(timestr," %d"":""%d", (int)(ovenData.time/SECperMIN), (ovenData.time%SECperMIN));
    }
    if (ovenData.state == COOKING){//cooking pixels to print string
        sprintf(topovenstr, "|" OVEN_TOP_ON OVEN_TOP_ON OVEN_TOP_ON OVEN_TOP_ON OVEN_TOP_ON "|");
        sprintf(botovenstr, "|" OVEN_BOTTOM_ON OVEN_BOTTOM_ON OVEN_BOTTOM_ON OVEN_BOTTOM_ON OVEN_BOTTOM_ON "|");
    }else{//not cooking pixels to print string
        sprintf(topovenstr, "|" OVEN_TOP_OFF OVEN_TOP_OFF OVEN_TOP_OFF OVEN_TOP_OFF OVEN_TOP_OFF "|");
        sprintf(botovenstr, "|" OVEN_BOTTOM_OFF OVEN_BOTTOM_OFF OVEN_BOTTOM_OFF OVEN_BOTTOM_OFF OVEN_BOTTOM_OFF "|");
    }
    if (ovenData.mode == BAKE && ovenData.state != COOKING){//bake printout based on where triangle goes
        if (ovenData.editing == TIME){
            sprintf(ovenstr, "%s MODE: BAKE\n|     | >TIME:%s\n|-----|  TEMP: "
                    "%d"DEGREE_SYMBOL"\n%s", topovenstr, timestr, ovenData.temperature, botovenstr);
        }else{
            sprintf(ovenstr, "%s MODE: BAKE\n|     |  TIME:%s\n|-----| >TEMP: "
                    "%d"DEGREE_SYMBOL"\n%s", topovenstr, timestr, ovenData.temperature, botovenstr);
        }
    }else if (ovenData.mode == TOAST){//toast screen printout
        sprintf(ovenstr, "%s MODE:TOAST\n|     | TIME:%s\n|-----|\n%s"
                , topovenstr, timestr, botovenstr);
    }else if (ovenData.mode == BROIL){//broil screen printout
        sprintf(ovenstr, "%s MODE: BROIL\n|     | TIME:%s\n|-----| TEMP: 500"
                DEGREE_SYMBOL"\n%s", topovenstr, timestr, botovenstr);
    }else{//bake screen printout without > for printout while cooking
        sprintf(ovenstr, "%s MODE: BAKE\n|     |  TIME:%s\n|-----|  TEMP: %d"
                DEGREE_SYMBOL"\n%s", topovenstr, timestr, ovenData.temperature, botovenstr);
    }
    OledDrawString(ovenstr);
    OledUpdate();
    //update OLED here
}

/*This function will execute your state machine.  
 * It should ONLY run if an event flag has been set.*/
void runOvenSM(void)
{
    if (ovenData.state == SETUP){
        OledSetDisplayNormal();//just in case
        if (ovenEvents.Btn4L == TRUE){//check to enter cooking mode
            ovenData.state = COOKING;
            ovenEvents.Btn4L = FALSE;
        }
        if (ovenData.mode == BAKE){//deciding whether pot adjustment adjusts time or temp
            if (ovenData.editing == TEMP){
                ovenData.temperature = (uint16_t)((AdcRead()*POTSLOPE)+temp_offset);
            }else if (ovenData.editing == TIME){
                ovenData.time = (uint16_t)((AdcRead()*POTSLOPE)+time_offset);
                ovenData.totaltime = (uint16_t)((AdcRead()*POTSLOPE)+time_offset);
            }
        }else{
            ovenData.time = (uint16_t)((AdcRead()*POTSLOPE)+time_offset);
            ovenData.totaltime = (uint16_t)((AdcRead()*POTSLOPE)+time_offset);
        }
        ovenEvents.ADC_CHANGED = FALSE;//notifying events that adc has been updated
    }else if(ovenData.state == SELECTOR_CHANGE_PENDING){//compute btn3 events
        if (ovenEvents.Btn3L == TRUE){
            if (ovenData.editing == TIME){
                ovenData.editing = TEMP;
            }else{
                ovenData.editing = TIME;
            }
            ovenEvents.Btn3L = FALSE;
        }
        if (ovenEvents.Btn3S == TRUE){
            if (ovenData.mode == BAKE){
                ovenData.mode = TOAST;
            }else if (ovenData.mode == TOAST){
                ovenData.mode = BROIL;
            }else if (ovenData.mode == BROIL){
                ovenData.mode = BAKE;
            }
            ovenEvents.Btn3S = FALSE;
        }
        if (ovenEvents.Btn4L == TRUE){
            ovenData.state = COOKING;
            ovenEvents.Btn4L = FALSE;
        }
    }else if(ovenData.state == COOKING){//compute cooking time display
        ovenData.time--;
        if (ovenData.time == ZERO){
            ovenData.state = RESET_PENDING;
        }
        if (ovenEvents.Btn4L == TRUE){
            ovenData.state = RESET_PENDING;
            ovenEvents.Btn4L = FALSE;
        }
        //compute which LEDs to trigger according cooking timer
        if ((((ovenData.totaltime - ovenData.time)*TotalLEDS)/ovenData.totaltime)>=EIGHT){
            ovenData.LEDS = noLEDSON;
        }else if ((((ovenData.totaltime - ovenData.time)*TotalLEDS)/ovenData.totaltime)>=SEVEN){
            ovenData.LEDS = oneLEDSON;
        }else if ((((ovenData.totaltime - ovenData.time)*TotalLEDS)/ovenData.totaltime)>=SIX){
            ovenData.LEDS = twoLEDSON;
        }else if ((((ovenData.totaltime - ovenData.time)*TotalLEDS)/ovenData.totaltime)>=FIVE){
            ovenData.LEDS = threeLEDSON;
        }else if ((((ovenData.totaltime - ovenData.time)*TotalLEDS)/ovenData.totaltime)>=FOUR){
            ovenData.LEDS = fourLEDSON;
        }else if ((((ovenData.totaltime - ovenData.time)*TotalLEDS)/ovenData.totaltime)>=THREE){
            ovenData.LEDS = fiveLEDSON;
        }else if ((((ovenData.totaltime - ovenData.time)*TotalLEDS)/ovenData.totaltime)>=TWO){
            ovenData.LEDS = sixLEDSON;
        }else if ((((ovenData.totaltime - ovenData.time)*TotalLEDS)/ovenData.totaltime)>=ONE){
            ovenData.LEDS = sevenLEDSON;
        }else if ((((ovenData.totaltime - ovenData.time)*TotalLEDS)/ovenData.totaltime)>=ZERO){
            ovenData.LEDS = eightLEDSON;
        }
        LEDS_SET(ovenData.LEDS);
    }else if(ovenData.state == RESET_PENDING){//invert display and reset back to setup with correct vars
        ovenData.flashes--;
        if (ovenData.flashes%TWO == ONE){
            OledSetDisplayInverted();
        }else{
            OledSetDisplayNormal();
        }
        if (ovenData.flashes == ZERO){
            ovenData.flashes = EIGHT;
            ovenData.state = SETUP;
            ovenData.time = ovenData.totaltime;
            LEDS_SET(ZERO);
        }
    }
    updateOvenOLED(ovenData);
}


int main()
{
    BOARD_Init();

     //initalize timers and timer ISRs:
    // <editor-fold defaultstate="collapsed" desc="TIMER SETUP">
    
    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.

    T2CON = 0; // everything should be off
    T2CONbits.TCKPS = 0b100; // 1:16 prescaler
    PR2 = BOARD_GetPBClock() / 16 / 100; // interrupt at .5s intervals
    T2CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T2IF = 0; //clear the interrupt flag before configuring
    IPC2bits.T2IP = 4; // priority of  4
    IPC2bits.T2IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T2IE = 1; // turn the interrupt on

    // Configure Timer 3 using PBCLK as input. We configure it using a 1:256 prescaler, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR3 to F_PB / 256 / 5 yields a .2s timer.

    T3CON = 0; // everything should be off
    T3CONbits.TCKPS = 0b111; // 1:256 prescaler
    PR3 = BOARD_GetPBClock() / 256 / 5; // interrupt at .5s intervals
    T3CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T3IF = 0; //clear the interrupt flag before configuring
    IPC3bits.T3IP = 4; // priority of  4
    IPC3bits.T3IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T3IE = 1; // turn the interrupt on;

    // </editor-fold>
   
    printf("Welcome to kgshah's Lab07 (Toaster Oven).  Compiled on %s %s.", __TIME__, __DATE__);

    //initialize state machine (and anything else you need to init) here
    LEDS_INIT();
    OledInit();
    ButtonsInit();
    AdcInit();
    updateOvenOLED(ovenData);

    while (1){
        if (ovenEvents.ADC_CHANGED){//when state machine should be updated
            runOvenSM();
            ovenEvents.ADC_CHANGED = FALSE;
        }
        if (ovenEvents.Btn3L || ovenEvents.Btn3S){
            runOvenSM();
            if (ovenData.state != COOKING){
                ovenData.state = SETUP;
            }
            ovenEvents.Btn3L = FALSE;
            ovenEvents.Btn3S = FALSE;
        }
        if (ovenEvents.Btn4L){
            runOvenSM();
            ovenEvents.Btn4L = FALSE;
        }
        //}

    };
}


/*The 5hz timer is used to update the free-running timer and to generate TIMER_TICK events*/
void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 12;

    //add event-checking code here
    TIMER_TICK++;//universal 5hz timer
    if (((TIMER_TICK%FIVE) == ZERO) && (ovenData.state == COOKING)){
        runOvenSM();//every 1 second while cooking decrement time by 1
    }
    if (((TIMER_TICK%TWO) == ZERO) && (ovenData.state == RESET_PENDING)){
        runOvenSM();//used to invert display every 2 ticks
    }
}


/*The 100hz timer is used to check for button and ADC events*/
void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;

    //add event-checking code here
    
    int btnH = ButtonsCheckEvents();//button debouncing and interpretation
    if (ovenData.state != COOKING){
        ovenEvents.ADC_CHANGED = AdcChanged();
        if (((btnH)&(BUTTON_EVENT_3DOWN)) == BUTTON_EVENT_3DOWN){//btn3 press
            ovenEvents.Btn3press_time = TIMER_TICK;
            ovenData.state = SELECTOR_CHANGE_PENDING;
        }
        if (((btnH)&(BUTTON_EVENT_3UP)) == (BUTTON_EVENT_3UP)){//btn 3 long release
            if ((TIMER_TICK - ovenEvents.Btn3press_time)>FIVE){
                ovenEvents.Btn3L = TRUE;
            }else{//btn 3 short release
                ovenEvents.Btn3S = TRUE;
            }
        }
    }
    if (((btnH)&(BUTTON_EVENT_4DOWN)) == (BUTTON_EVENT_4DOWN)){//btn4 press
        ovenEvents.Btn4press_time = TIMER_TICK;
    }
    if (((btnH)&(BUTTON_EVENT_4UP)) == (BUTTON_EVENT_4UP)){//btn4 release
        if ((TIMER_TICK - ovenEvents.Btn4press_time)>FIVE){
            ovenEvents.Btn4L = TRUE;
        }
    }
}