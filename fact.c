#include <lpc214x.h>

void inti_pll(void) {
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

void delay_ms(int ms) {
    T0PR = 60000 - 1;
    T0TCR = 0x02;
    T0TC = 0;
    T0TCR = 0x01;
    while(T0TC < ms);
    T0TCR = 0x00;
}

int main(void) {
    int n = 6;   // upto 6! because LEDs can display max 720
    int i, j, fact;

    inti_pll();
    PINSEL0 = 0x00000000;
    IODIR0 |= 0x000003FF;

    while(1) {
        for(i = 1; i <= n; i++) {

            fact = 1;
            for(j = 1; j <= i; j++)
                fact *= j;   // factorial calculation

            IOSET0 = fact;
            delay_ms(300);
            IOCLR0 = 0x000003FF;
            delay_ms(150);
        }
    }
}
