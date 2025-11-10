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
    unsigned int n = 5;
    unsigned long long fact = 1;
    int i;

    init_pll();
    PINSEL0 = 0x00000000;
    IO0DIR  = 0x000003FF; // LEDs on P0.0 - P0.9

    // Calculate factorial
    for(i = 1; i <= n; i++) {
        fact *= i;
    }

    // Display factorial value on LEDs (for simplicity, only lower 10 bits)
    IO0SET = fact & 0x000003FF;
    delay_ms(1000);
    IO0CLR = 0x000003FF;

    while(1); // Stop here
}