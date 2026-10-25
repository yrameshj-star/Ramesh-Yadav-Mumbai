/*
 * PIC16F877A LED Blink + Button (LED जलना-बुझना, बटन के साथ)
 *
 * Compiler : MPLAB XC8
 * Clock    : 20 MHz crystal (HS mode), OSC1/OSC2 pin पर
 * LED      : RB0 (pin 33) -> 330 ohm resistor -> LED -> GND
 * Button   : RB1 (pin 34) -> push button -> GND
 *            (PORTB का internal pull-up इस्तेमाल होता है, बाहरी resistor ज़रूरी नहीं)
 *
 * LED हर 500 ms पर on/off होती है (1 सेकंड में एक blink)।
 * बटन दबाने पर blinking रुक जाती है (LED बंद), दोबारा दबाने पर फिर शुरू होती है।
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
#define BTN_TRIS    TRISBbits.TRISB1    // RB1 की दिशा
#define BTN         PORTBbits.RB1       // RB1 pin (दबाने पर 0, छोड़ने पर 1)

#define TICK_MS         10      // Loop हर 10 ms पर चलता है
#define BLINK_TICKS     50      // 50 x 10 ms = 500 ms
#define DEBOUNCE_TICKS  3       // बटन 30 ms तक स्थिर रहे तभी मानो

void main(void)
{
    unsigned char blinking = 1;     // 1 = blink चालू, 0 = रुका हुआ
    unsigned char ledState = 0;     // LED की मौजूदा स्थिति
    unsigned char btnStable = 1;    // बटन की debounce की हुई स्थिति (1 = छूटा हुआ)
    unsigned char btnCount = 0;     // Debounce counter
    unsigned char ticks = 0;        // Blink timer counter

    OPTION_REGbits.nRBPU = 0;       // PORTB के internal pull-up चालू
    LED_TRIS = 0;                   // RB0 को output बनाओ
    BTN_TRIS = 1;                   // RB1 को input बनाओ
    LED = 0;                        // शुरुआत में LED बंद

    while (1)                       // हमेशा चलने वाला loop
    {
        __delay_ms(TICK_MS);

        // बटन debounce: नई स्थिति लगातार DEBOUNCE_TICKS बार दिखे तभी स्वीकार करो
        if (BTN == btnStable)
        {
            btnCount = 0;
        }
        else if (++btnCount >= DEBOUNCE_TICKS)
        {
            btnStable = BTN;
            btnCount = 0;
            if (btnStable == 0)     // बटन अभी दबाया गया
            {
                blinking = !blinking;
                ticks = 0;
            }
        }

        // LED blink
        if (blinking)
        {
            if (++ticks >= BLINK_TICKS)
            {
                ticks = 0;
                ledState = !ledState;   // LED उलटो (on <-> off)
            }
        }
        else
        {
            ledState = 0;               // रुका हुआ: LED बंद
        }

        LED = ledState;
    }
}
