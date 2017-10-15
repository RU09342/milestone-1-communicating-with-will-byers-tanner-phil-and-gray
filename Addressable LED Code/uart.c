/*
 * uart.c
 *
 *  Created on: Oct 13, 2017
 *      Author: Tanner
 */

#include <msp430g2553.h>
#include "uart.h"
#include "pwm.h"

int new_red, new_green, new_blue = 0;
int bytecount = 0;
int numBytes = 0;
int tempBuf = 0;

void UART_Init(){

    //UART Config
    if (CALBC1_1MHZ==0xFF){                 // If calibration constant erased
        while(1);                               // do not load, trap CPU!!
    }
    WDTCTL = WDTPW | WDTHOLD;                 // stop watchdog timer
    DCOCTL = 0;                               // Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
    DCOCTL = CALDCO_1MHZ;
    P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
    P1SEL2 = BIT1 + BIT2 ;                    // P1.1 = RXD, P1.2=TXD
    UCA0CTL1 |= UCSSEL_2;                     // SMCLK
    UCA0BR0 = 104;                            // 1MHz 9600
    UCA0BR1 = 0;                              // 1MHz 9600
    UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
    IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt

}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?
    tempBuf = UCA0RXBUF;

    switch(bytecount){
        case 0: numBytes = UCA0RXBUF;
              break;
        case 1: new_red = UCA0RXBUF;
              break;
        case 2: new_green = UCA0RXBUF;
              break;
        case 3: new_blue = UCA0RXBUF;
              UCA0TXBUF = numBytes-3;
              SetRed(new_red);
              SetBlue(new_blue);
              SetGreen(new_green);
              break;
        default:
          if(bytecount<numBytes)
          {
              UCA0TXBUF = UCA0RXBUF;
          }
          else{
              bytecount = -1;
          }

        }
    bytecount++;
}


