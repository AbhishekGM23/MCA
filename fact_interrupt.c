#include <lpc214x.h>

unsigned int mode = 0; // used to toggle LED using interrupt

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

// Interrupt Service Routine
void EXTINT0_ISR(void) __irq {
    mode = !mode;         // toggle mode each button press
    EXTINT = 0x01;        // clear interrupt flag
    VICVectAddr = 0x00;   // end of interrupt
}

int main(){
    unsigned int n = 5;
    unsigned long long fact = 1;
    int i;

    init_pll();
    PINSEL0 = 0x00000000;
    IO0DIR = 0x000003FF;

    // Configure EINT0 on P0.14
    PINSEL0 |= (1<<29);
    EXTMODE = 0x01;       
    EXTPOLAR = 0x00;      
    VICIntSelect = 0x00;
    VICVectAddr0 = (unsigned int)EXTINT0_ISR;
    VICVectCntl0 = 0x20 | 14;
    VICIntEnable = (1<<14);

    while(1){
        if(mode == 0){
            // Normal LED pattern
            IO0SET = 0x00000001;
            delay_ms(300);
            IO0CLR = 0x000003FF;
        } else {
            // Factorial display
            fact = 1;
            for(i = 1; i <= n; i++)
                fact *= i;

            IO0SET = fact & 0x000003FF;
            delay_ms(1000);
            IO0CLR = 0x000003FF;
        }
    }
}