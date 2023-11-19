
//******************************************************************************
//  MSP430F552x Demo - Timer1_A3, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software and TA_1 ISR. Toggles every
//  50000 SMCLK cycles. SMCLK provides clock source for TACLK.
//  During the TA_1 ISR, P1.0 is toggled and 50000 clock cycles are added to
//  CCR0. TA_1 ISR is triggered every 50000 cycles. CPU is normally off and
//  used only during TA_ISR.
//  ACLK = n/a, MCLK = SMCLK = TACLK = default DCO ~1.045MHz
//
//           MSP430F552x
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |               |
//        |           P1.0|-->LED
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430.h>


#define TX_MSG_SIZE 4U
void main() {
    WDTCTL = WDTPW | WDTHOLD; // Stop the watchdog timer

    // Configure P1.3 as an input (default configuration)
    P1DIR &= ~BIT3;

    // Configure P1.0 as an output
    P1DIR |= BIT4;
    uint8_t u08_txMessage[TX_MSG_SIZE] = {"H","O","L","A"};

    while (1) {

        vfn_TXRX_readMessage();
        u16_TXRX_sendMessage(u08_txMessage, TX_MSG_SIZE);
        __delay_cycles(1000);
        // Read the input value of P1.3
        /* if (P1IN & BIT3) {
            // P1.3 is high, turn on the LED on P1.0
            P1OUT |= BIT0;
        } else {
            // P1.3 is low, turn off the LED on P1.0
            P1OUT &= ~BIT0;
        } */
    }
}
/* In this code:

We configure P1.3 as an input by clearing the corresponding bit in P1DIR.
We configure P1.0 as an output by setting the corresponding bit in P1DIR.
In the main loop, we continuously read the input value of P1.3 using the P1IN register and check if bit 3 (BIT3) is set (high). If P1.3 is high, we turn on the LED on P1.0 (set bit 0 of P1OUT), and if P1.3 is low, we turn off the LED on P1.0 (clear bit 0 of P1OUT).
Ensure that you connect the input (P1.3) to an appropriate voltage level (e.g., a button or a digital signal source) and connect the LED (P1.0) with a current-limiting resistor to observe the LED's behavior based on the input signal.

 */



