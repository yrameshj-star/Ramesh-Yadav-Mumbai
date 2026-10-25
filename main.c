/*
 * PIC16F877A LED Blink (LED जलना-बुझना)
 *
 * Compiler : MPLAB XC8
 * Clock    : 20 MHz crystal (HS mode), OSC1/OSC2 pin पर
 * LED      : RB0 (pin 33) -> 330 ohm resistor -> LED -> GND
 *
 * LED हर 500 ms पर on/off होती है (1 सेकंड में एक blink)।
 */

// Configuration bits (chip की सेटिंग)
#pragma config FOSC = HS        // HS oscillator (20 MHz crystal)
#pragma config WDTE = OFF       // Watchdog timer बंद
#pragma config PWRTE = ON       // Power-up timer चालू
#pragma config BOREN = ON       // Brown-out reset चालू
#pragma config LVP = OFF        // Low-voltage programming बंद (RB3 सामान्य I/O)
#pragma config CPD = OFF        // Data EEPROM code protection बंद
#pragma config WRT = OFF        // Flash write protection बंद
#pragma config CP = OFF         // Flash code protection बंद

#include <xc.h>

#define _XTAL_FREQ 20000000UL   // Crystal frequency, __delay_ms() के लिए ज़रूरी

#define LED_TRIS    TRISBbits.TRISB0    // RB0 की दिशा (input/output)
#define LED         PORTBbits.RB0       // RB0 pin

void main(void)
{
    LED_TRIS = 0;               // RB0 को output बनाओ
    LED = 0;                    // शुरुआत में LED बंद

    while (1)                   // हमेशा चलने वाला loop
    {
        LED = 1;                // LED चालू
        __delay_ms(500);        // 500 ms रुको
        LED = 0;                // LED बंद
        __delay_ms(500);        // 500 ms रुको
    }
}
