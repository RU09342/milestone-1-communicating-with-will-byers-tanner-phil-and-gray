#include <msp430g2553.h>
#include <pwm.h>
#include "uart.h"

static const int initial_red = 255;
static const int initial_green = 69;
static const int initial_blue = 00;


int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                                   // Stop Watch Dog Timer

    PWM_Init(initial_red, initial_green, initial_blue);         // Initialize PWM and Initial Colors

    UART_Init();                                                // Initialize UART to 9600 BaudRate and Setup Interrupt

    __bis_SR_register(LPM0_bits + GIE);                         // Enter LPM0, interrupts enabled
}
