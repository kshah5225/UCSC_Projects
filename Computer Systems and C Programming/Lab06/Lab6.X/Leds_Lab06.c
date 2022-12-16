/* Kunal Shah kgshah@ucsc.edu
 * File:   Leds_Lab06.c
 * Author: kgshah
 *
 * Created on February 8, 2022, 11:00 AM
 */

#include "Leds_Lab06.h"

#include <xc.h>
#include <sys/attribs.h>

void LEDS_INIT(void){
    TRISE = 0x00; // 0000 0000 Initilize LEDs pins to output
    LATE = 0x00; // 0000 0000 Ensure LEDs are set to LOW(aka off))
}

void LEDS_SET(char newPattern){
    LATE = newPattern;//set register to new led pattern
}

char LEDS_GET(void){
    return LATE;//return current led pattern
}