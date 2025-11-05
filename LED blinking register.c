/********************************************************/
/* This Program is to demonstrate LED Blinking  			  */
/********************************************************
Author          : Abhaya Y, Abhishek G M
Board           : ARM7 Development Board
Processor       : LPC2148
Port 1          : P1.16 - P1.23
********************************************************/
#include <lpc214x.h> //header file
void delay(unsigned time)
{
	unsigned int i, j;   //delay function
	for(i=0; i<time; i++);
	for(j=0; j<1275; j++);
}

int main(void) {
	IO1DIR=0X00FF0000; //direction set to output port1 (P1.16 - P1.23)
	while(1)
	{
		IO1SET=0X00660000; //P1.17,18,21,22 is set to high
		delay(500);
		IO1CLR=0X00660000; //P1.17,18,21,22 is set to low
		delay(500);
		
		IO1SET=0X00CC0000; //P1.18,19,22,23 is set to high
		delay(500);
		IO1CLR=0X00CC0000; //P1.18,19,22,23 is set to low
		delay(500);
		
		IO1SET=0X00990000; //P1.16,19,20,23 is set to high
		delay(500);
		IO1CLR=0X00990000; //P1.16,19,20,23 is set to low
		delay(500);
		
		IO1SET=0X00330000; //P1.16,17,20,21 is set to high
		delay(500);
		IO1CLR=0X00330000; //P1.16,17,20,21 is set to low
		delay(500);
	}
}
