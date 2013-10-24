/**
 ** lcd.h
 **
 ** Created on: Oct 22, 2013
 **      Author: C15Andrew.Tymchenko
 **      Description: Library to interact with the Geek Box LCD.
 **/

#ifndef LCD_H_
#define LCD_H_

void initSPI();
void LCDinit();
void LCDclear();
void cursorToLineTwo();
void cursorToLineOne();
void writeChar(char asciiChar);
void writeString(char * string);
void scrollSrting(char * string, char *string2);

#endif /* LCD_H_ */
