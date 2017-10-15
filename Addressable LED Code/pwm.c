/*
 * pwm_rgb.c
 *
 *  Created on: Oct 13, 2017
 *      Author: Tanner
 */


#include <msp430g2553.h>
#include "pwm.h"
#include "Tanner's MSP Lib/timer/timer.h"

int count = 0;
int count2 = 0;

void PWM_Init(int red, int green, int blue){

    /* Initialize Timer A and B to run at 250kHz in up mode
     * CCR0 is set to 256 since that is the resolution of
     * each color.
     */
    TimerA_Init(SMCLK, UP, DIV4, 256);
    TimerB_Init(SMCLK, UP, DIV4, 256);

    /* Configure P1.6 to output Red PWM
     * Used an array of values to linearize
     * the brightness to human eyes.
     */
    TimerA_SetCompareVal1(linear_brightness_curve[red]);
    P1DIR |= BIT6;
    P1SEL |= BIT6;
    P1SEL2 = 0;
    TA0CCTL1 |= OUTMOD_7;


    /* Configure P2.1 to output Green PWM
     * Used an array of values to linearize
     * the brightness to human eyes.
     */
    TimerB_SetCompareVal1(linear_brightness_curve[green]);
    P2DIR |= BIT1;
    P2SEL |= BIT1;
    P2SEL2 = 0;
    TA1CCTL1 |= OUTMOD_7;

    /* Configure P2.4 to output Blue PWM
     * Used an array of values to linearize
     * the brightness to human eyes.
     */
    TimerB_SetCompareVal2(linear_brightness_curve[blue]);
    P2DIR |= BIT4;
    P2SEL |= BIT4;
    P2SEL2 = 0;
    TA1CCTL2 |= OUTMOD_7;

}

/* Set Red PWM value */
void SetRed(int red){
    TimerA_SetCompareVal1(linear_brightness_curve[red]);
}

/* Set Green PWM value */
void SetGreen(int green){
    TimerB_SetCompareVal1(linear_brightness_curve[green]);
}

/* Set Blue PWM value */
void SetBlue(int blue){
    TimerB_SetCompareVal2(linear_brightness_curve[blue]);
}
