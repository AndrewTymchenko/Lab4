#include <msp430.h> 
#include "lcd.h"

/**
 ** main.c
 **
 ** Author: Andrew Tymchenko
 ** Description: Initializes SPI and LCD.
 ** Scrolls two messages, one on the top line and one on the bottom line.
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    initSPI();
    LCDinit();
    LCDclear();

    cursorToLineTwo();
    writeString("Beasty Boys#");

    while(1){

    }
	
	return 0;
}
