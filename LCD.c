/*
 * LCD.c
 *
 *  Created on: Oct 23, 2013
 *      Author: C15Andrew.Tymchenko
 */

#include <msp430.h>
#include "lcd.h"


#define RS_MASK 0x40

char LCDCON = 0;

void writeCommandNibble(char commandNibble);
void writeCommandByte(char commandByte);
void writeDataByte(char dataByte);
void LCD_write_8(char byteToSend);
void LCD_write_4(char byteToSend);
void SPI_send(char byteToSend);
void set_SS_lo();
void set_SS_hi();

void initSPI(){
        UCB0CTL1 |= UCSWRST;

        UCB0CTL0 |= UCCKPL|UCMSB|UCMST|UCSYNC;

        UCB0CTL1 |= UCSSEL1;

        UCB0STAT |= UCLISTEN;

        P1SEL |= BIT5|BIT6|BIT7;        //Clk(P1.5), SOMI(P1.6), SIMO(P1.7)
        P1SEL2 |= BIT5|BIT6|BIT7;

        P2DIR |= BIT1;                //GPIO for SS

        UCB0CTL1 &= ~UCSWRST;

}

void LCDinit()
{
    writeCommandNibble(0x03);

    writeCommandNibble(0x03);

    writeCommandNibble(0x03);

    writeCommandNibble(0x02);

    writeCommandByte(0x28);

    writeCommandByte(0x0C);

    writeCommandByte(0x01);

    writeCommandByte(0x06);

    writeCommandByte(0x01);

    writeCommandByte(0x02);

    SPI_send(0);
    __delay_cycles(47);
}


void LCDclear()
{
    writeCommandByte(1);
}

void cursorToLineOne(){
	writeCommandByte(0x02);
}

void cursorToLineTwo(){
	writeCommandByte(0x02);
	writeCommandByte(0x0F);
	int i;
	for(i = 0; i < 40; i++){
		writeCommandByte(0x14);
	}
}

void scrollString(char * string, char *string2){
	cursorToLineOne();
	writeString(string);

	cursorToLineTwo();
	writeString(string2);
}

void writeString(char * string){
	while(*string != '#'){
		writeChar(*string);
		string++;
	}

}

void writeChar(char asciiChar){
	writeDataByte(asciiChar);
}

void set_SS_lo(){
        P2OUT &= ~BIT1;
}

void set_SS_hi(){
        P2OUT |= BIT1;
}


void writeCommandNibble(char commandNibble)
{
    LCDCON &= ~RS_MASK;
    LCD_write_4(commandNibble);
    __delay_cycles(1893);
}

void writeCommandByte(char commandByte)
{
    LCDCON &= ~RS_MASK;
    LCD_write_8(commandByte);
    __delay_cycles(1893);
}

void writeDataByte(char dataByte)
{
    LCDCON |= RS_MASK;
    LCD_write_8(dataByte);
    __delay_cycles(1893);
}

void LCD_write_8(char byteToSend)
{
    unsigned char sendByte = byteToSend;

    sendByte &= 0xF0;

    sendByte = sendByte >> 4;               // rotate to the right 4 times

    LCD_write_4(sendByte);

    sendByte = byteToSend;

    sendByte &= 0x0F;

    LCD_write_4(sendByte);
}

void LCD_write_4(char byteToSend)
{
    unsigned char sendByte = byteToSend;

    sendByte &= 0x0F;

    sendByte |= LCDCON;

    sendByte &= 0x7F;

    SPI_send(sendByte);

    __delay_cycles(47);

    sendByte |= 0x80;

    SPI_send(sendByte);

    __delay_cycles(47);

    sendByte &= 0x7F;

    SPI_send(sendByte);

    __delay_cycles(47);
}
void SPI_send(char byteToSend)
{
    volatile char readByte;

    set_SS_lo();

    UCB0TXBUF = byteToSend;

    while(!(UCB0RXIFG & IFG2))
    {
        // wait until you've received a byte
    }

    readByte = UCB0RXBUF;

    set_SS_hi();
}


