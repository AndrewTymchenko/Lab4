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


    char* string = "ECE382 is my favorite class!";
    char* string2 = "Beasty Boys";
    scrollString(string, string2);


    while(1){

    }
	
	return 0;
}
