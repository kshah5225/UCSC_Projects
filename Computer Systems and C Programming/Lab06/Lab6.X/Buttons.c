/* Kunal Shah kgshah@ucsc.edu
 * File:   Buttons.c
 * Author: kgshah
 *
 * Created on February 8, 2022, 11:00 AM
 */

#include "Buttons.h"
#include "BOARD.h"

static int BT = 0;//debounce timer
static uint8_t PBS = 0;//previous button state

void ButtonsInit(void){//init pins for buttons
    TRISD |= 0x00E0;
    TRISF |= 0x0002;
}

uint8_t ButtonsCheckEvents(void){
    uint8_t CBS = BUTTON_STATES();
    if (CBS==PBS || BT>0){//if no changes are made or if debounce timer hasent reset return BUTTON_EVENT_NONE
        if (BT>0){
            BT--;
        }
        return BUTTON_EVENT_NONE;
    }
    BT = BUTTONS_DEBOUNCE_PERIOD;//making sure to not let updates occur for another 4 cycles
    uint8_t CIBS = CBS^PBS;//change in button state(binary)
    uint8_t FiBM = 1;//1st button mask
    uint8_t SeBM = 2;//2nd button mask
    uint8_t ThBM = 4;//3rd button mask
    uint8_t FoBM = 8;//4th button mask
    uint8_t BoneS = (CIBS&FiBM);//did first bit change?
    uint8_t BtwoS = (CIBS&SeBM)>>1;//did second bit change?
    uint8_t BthreeS = (CIBS&ThBM)>>2;//did third bit change?
    uint8_t BfourS = (CIBS&FoBM)>>3;//did fourth bit change?
    int BoneFS = ((CBS&FiBM)+1)*BoneS;//converting into an or-able form
    int BtwoFS = (((CBS&SeBM)>>1)+1)*BtwoS*0x04;//converting into an or-able form
    int BthreeFS = (((CBS&ThBM)>>2)+1)*BthreeS*0x10;//converting into an or-able form
    int BfourFS = (((CBS&FoBM)>>3)+1)*BfourS*0x40;//converting into an or-able form
    PBS = CBS;//setting current buttons to previous buttons
    return(BoneFS|BtwoFS|BthreeFS|BfourFS);//or-ing all bits together
    
    
}