#include <lpc214x.h>

void inti_pll(void) {
    PLL0CON = 0x01;
    PLL0CFG = 0x24;
    PLL0FEED = 0xAA;
    PLL0FEED = 0x55;

    while(!(PLL0STAT & (1<<10)));  // Wait for PLL lock

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

int is_prime(int num) {
    int i;
    if(num <= 1) return 0;
    for(i = 2; i * i <= num; i++) {
        if(num % i == 0)
            return 0;
    }
    return 1;
}

int main(void) {
    int count = 0;
    int number = 2;  // Start checking from 2 (first prime)

    inti_pll();
    PINSEL0 = 0x00000000;
    IODIR0 |= 0x000003FF;  // P0.0–P0.9 as output

    while(1) {
        count = 0;
        number = 2;

        while(count < 10) {       // First 10 prime numbers
            if(is_prime(number)) {
                IOSET0 = number;       // Display prime number in binary
                delay_ms(400);
                IOCLR0 = 0x000003FF;   // Clear LEDs
                delay_ms(200);
                count++;
            }
            number++;
        }
    }
}
