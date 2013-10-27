#include <msp430.h> 
#include "lcd.h"
#include "button.h"

/**
 ** main.c
 **
 ** Author: Andrew Tymchenko
 ** Description: Initializes SPI and LCD.
 ** Scrolls two messages, one on the top line and one on the bottom line.
 ** B functionality, asks which message to display.
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    initSPI();
    LCDinit();
    LCDclear();

    configureP2PinAsButton(BIT3|BIT4|BIT5);
        char* string = "ECE382 is my favorite class! ";
        char* string2;

        writeString("Message?");
        cursorToLineTwo();
        writeString("PRESS123");

        char buttons[] = {BIT3, BIT4, BIT5};
        char pressedButton = pollP2Buttons(buttons, 3);

        if(pressedButton == BIT3){
                string2 = "Button 1. ";
                waitForP2ButtonRelease(BIT3);
        }
        else if(pressedButton == BIT4){
                string2 = "Button 2. ";
                waitForP2ButtonRelease(BIT4);
        }
        else{
                string2 = "Button 3. ";
                waitForP2ButtonRelease(BIT5);
        }

        scrollString(string, string2);

        //traps cpu
        while(1){

        }

            return 0;
    }

