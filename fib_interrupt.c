#include <lpc214x.h>

unsigned int mode = 0;

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

void EXTINT0_ISR(void) __irq {
    mode = !mode;
    EXTINT = 0x01;
    VICVectAddr = 0x00;
}

int main(){
    int n = 10, a = 0, b = 1, next, i;

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
            IO0SET = 0x00000001;
            delay_ms(400);
            IO0CLR = 0x000003FF;
        } else {
            a = 0;
            b = 1;
            for(i = 0; i < n; i++){
                if(i <= 1)
                    next = i;
                else {
                    next = a + b;
                    a = b;
                    b = next;
                }
                IO0SET = next & 0x000003FF;
                delay_ms(300);
                IO0CLR = 0x000003FF;
            }
        }
    }
}