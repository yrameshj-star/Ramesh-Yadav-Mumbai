/*
 * PIC16F877A LED blink
 *
 * Compiler : MPLAB XC8
 * Clock    : 20 MHz crystal (HS mode) on OSC1/OSC2
 * LED      : RB0 (pin 33) -> 330R resistor -> LED -> GND
 *
 * The LED toggles every 500 ms (1 Hz blink).
 */

// Configuration bits
#pragma config FOSC = HS        // HS oscillator (20 MHz crystal)
#pragma config WDTE = OFF       // Watchdog timer disabled
#pragma config PWRTE = ON       // Power-up timer enabled
#pragma config BOREN = ON       // Brown-out reset enabled
#pragma config LVP = OFF        // RB3 is digital I/O, HV programming only
#pragma config CPD = OFF        // Data EEPROM code protection off
#pragma config WRT = OFF        // Flash write protection off
#pragma config CP = OFF         // Flash code protection off

#include <xc.h>

#define _XTAL_FREQ 20000000UL   // Used by __delay_ms()

#define LED_TRIS    TRISBbits.TRISB0
#define LED         PORTBbits.RB0

void main(void)
{
    LED_TRIS = 0;               // RB0 as output
    LED = 0;                    // Start with LED off

    while (1)
    {
        LED = 1;                // LED on
        __delay_ms(500);
        LED = 0;                // LED off
        __delay_ms(500);
    }
}
