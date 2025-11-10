#include <lpc214x.h>

void init_pll(void){
    PLL0CON = 0x01;     
    PLL0CFG = 0x24;     
    PLL0FEED = 0xAA;    
    PLL0FEED = 0x55;    
    while(!(PLL0STAT & (1<<10))); 
    PLL0CON = 0x03;     
    PLL0FEED = 0xAA;    
    PLL0FEED = 0x55;    
    VPBDIV = 0x01;      
}

void delay_ms(int ms){
    T0PR = 60000 - 1;   
    T0TCR = 0x02;       
    T0TC = 0;
    T0TCR = 0x01;
    while(T0TC < ms);
    T0TCR = 0x00;
}

int main(){
    int n = 17, i, isPrime = 1;

    init_pll();
    PINSEL0 = 0x00000000;
    IO0DIR  = 0x000003FF; // LEDs on P0.0 - P0.9

    // Check if prime
    if(n <= 1) isPrime = 0;
    else {
        for(i = 2; i <= n/2; i++) {
            if(n % i == 0) {
                isPrime = 0;
                break;
            }
        }
    }

    if(isPrime) {
        IO0SET = 0x00000001;  // Turn ON LED on P0.0 for Prime
    } else {
        IO0SET = 0x00000002;  // Turn ON LED on P0.1 for Not Prime
    }

    delay_ms(2000);
    IO0CLR = 0x000003FF;

    while(1); // Stop here
}