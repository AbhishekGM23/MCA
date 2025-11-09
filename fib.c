/*************************************************************************************************************
Problem: N Fibanocci seris no printing on LED and delay using timer
Author:Abhaya Y
Board: LPC2148
Pin: P0.0-P0.10 to LED
****************************************************************************************************************/
#include<lpc214x.h>
void init_pll(void){
	PLL0CON=0X01;
	PLL0CFG=0X24;
	PLL0FEED=0XAA;
	PLL0FEED=0X55;
	while(!(PLL0STAT &(1<<10)));
	PLL0CON=0X03;
	PLL0FEED=0XAA;
	PLL0FEED=0X55;
	VPBDIV=0X01;
}
void delay_ms(int ms){
	T0PR=60000-1;
	T0TCR=0X02;
	T0TC=0;
	T0TCR=0X01;
	while(T0TC<ms);
	T0TCR=0X00;
}
int main(){
	int n=17;
	init_pll();
	PINSEL0 |=0X00000000;
	IO0DIR |=0X000003FF;
	while(1){
	 int a=0,b=1,next,i;	
    for ( i = 0; i < n; i++) {
        if (i <= 1) {
            next = i;
        } else {
            next = a + b;
            a = b;
            b = next;
        }
        IO0SET |=next;
				delay_ms(100);
				IO0CLR |=0X000003FF;
    }
	}
}

