/*
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

void gpio_setup(void) {

rcc_periph_clock_enable(RCC_GPIOC);

gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL,
		   GPIO14);

}

int main(void) {
gpio_setup();

while(1) {
gpio_toggle(GPIOC, GPIO14);

for(int i=0; i<50000; i++)
 __asm__("nop");
}

}
*/


/**************************************************************************/
/*
//PUSH BUTTON
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

static void gpio_setup(void) {

rcc_periph_clock_enable(RCC_GPIOC);
rcc_periph_clock_enable(RCC_GPIOA);

gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO14);
		   
gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, GPIO7);
gpio_clear(GPIOA, GPIO7);

}

int main(void) {

gpio_setup();

while(1) {
 if(gpio_get(GPIOA, GPIO7)==0)
 {
 gpio_clear(GPIOC, GPIO14);
  } else {
 gpio_set(GPIOC, GPIO14);
 }
 
 for(int i=0; i<5000; i++)
 __asm__("nop");
 }
 return 0;
 }
 */
 
/**************************************************************************/
/*
//PUSH BUTTON INTERRUPT 
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/cm3/nvic.h>


static void gpio_setup(void) {
    // Enable GPIOA and GPIOC clock
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOC);

    // Set PC13 as push-pull output (LED)
    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ,
                  GPIO_CNF_OUTPUT_PUSHPULL, GPIO14);
//    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ,
 //                 GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);

    // Set PA0 as input with pull-down (Button)
    gpio_set_mode(GPIOA, GPIO_MODE_INPUT,
                  GPIO_CNF_INPUT_PULL_UPDOWN, GPIO7);
    gpio_clear(GPIOA, GPIO7); // Enable pull-down
}

static void exti_setup(void) {
    // Enable AFIO clock
    rcc_periph_clock_enable(RCC_AFIO);

    // Map EXTI0 line to PA0
    exti_select_source(EXTI0, GPIOA);

    // Configure EXTI0 to trigger on rising edge
    exti_set_trigger(EXTI0, EXTI_TRIGGER_RISING);
    exti_enable_request(EXTI0);

    // Enable EXTI0 interrupt in NVIC
    nvic_enable_irq(NVIC_EXTI0_IRQ);
}

// Interrupt handler
void exti0_isr(void) {
    // Check if EXTI0 interrupt occurred
    if (exti_get_flag_status(EXTI0)) {
       for (int i=0;i<72000000; i++) 
        __asm__("nop");
        gpio_set(GPIOC, GPIO14); // Toggle LED 
 	for (int i=0;i<72000000; i++) 
	__asm__("nop");
	gpio_clear(GPIOC, GPIO14); 
       exti_reset_request(EXTI0);  // Clear interrupt flag

    }
}

int main(void) {
    gpio_setup();
    exti_setup();

    while (1) {
        // Main loop does nothing; interrupt handles button press


	__asm__("nop");



    }

    return 0;
}
*/

/**************************************************************************/
/*
//DUTY CYCLE
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

static void gpio_setup(void) {
    rcc_periph_clock_enable(RCC_GPIOC);

    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ,
                  GPIO_CNF_OUTPUT_PUSHPULL, GPIO14 | GPIO15);
}

int main(void) {
    gpio_setup();

    while (1) {

           //LED1 → 25% duty cycle (PC13)

        gpio_set(GPIOC, GPIO14);  // ON
        for (volatile int i = 0; i < 200000; i++)
            __asm__("nop");

        gpio_clear(GPIOC, GPIO14); // OFF
        for (volatile int i = 0; i < 600000; i++)
            __asm__("nop");


      
           //LED2 → 75% duty cycle (PC14)
         
        gpio_set(GPIOC, GPIO15);  // ON
        for (volatile int i = 0; i < 600000; i++)
            __asm__("nop");

        gpio_clear(GPIOC, GPIO15); // OFF
        for (volatile int i = 0; i < 200000; i++)
            __asm__("nop");
    }

    return 0;
}
*/

/**************************************************************************/
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

static void pwm_setup(void) {
    /* Enable clocks */
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_TIM2);

    /* PA0 = TIM2_CH1 (AF push-pull) */
    gpio_set_mode(GPIOA,
                  GPIO_MODE_OUTPUT_2_MHZ,
                  GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,
                  GPIO0);

    /* Timer settings */
   // timer_reset(TIM2);

    /* PWM Frequency = 1 kHz  (example) */
    timer_set_prescaler(TIM2, 72 - 1);     // 72 MHz / 72 = 1 MHz timer clock
    timer_set_period(TIM2, 1000 - 1);      // 1 MHz / 1000 = 1 kHz PWM

    /* PWM Mode 1 on TIM2_CH1 */
    timer_set_oc_mode(TIM2, TIM_OC1, TIM_OCM_PWM1);
    timer_enable_oc_output(TIM2, TIM_OC1);
    timer_set_oc_value(TIM2, TIM_OC1, 0);  // Start with 0% duty

    /* Start timer */
    timer_enable_counter(TIM2);
}

int main(void) {

    pwm_setup();

    /* Duty cycle sequence */
    int duty_steps[] = {250, 500, 750, 1000};  // 25%, 50%, 75%, 100%
    int index = 0;

    while (1) {

        timer_set_oc_value(TIM2, TIM_OC1, duty_steps[index]);

        /* Small CPU pause (NOT delay brightness, just step timing) */
        for (int i = 0; i < 3000000; i++)
            __asm__("nop");

        index++;
        if (index > 3)
            index = 0;
    }

    return 0;
}
