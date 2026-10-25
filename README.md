# PIC16F877A LED Blink

PIC16F877A के RB0 pin पर लगी LED को 1 Hz पर blink करता है (500 ms चालू, 500 ms बंद)।

RB1 पर लगा बटन दबाने से blinking रुक जाती है (LED बंद), दोबारा दबाने पर फिर शुरू हो जाती है।

## Hardware (वायरिंग)

| कनेक्शन | विवरण |
|---|---|
| VDD (pin 11, 32) | +5 V |
| VSS (pin 12, 31) | GND |
| MCLR (pin 1) | 10 kΩ resistor से +5 V |
| OSC1/OSC2 (pin 13, 14) | 20 MHz crystal, दोनों pin से GND तक 22 pF capacitor |
| RB0 (pin 33) | 330 Ω resistor → LED का anode (+), LED का cathode (−) → GND |
| RB1 (pin 34) | Push button → GND (internal pull-up चालू है, बाहरी resistor ज़रूरी नहीं) |

Chip के पास VDD और VSS के बीच 100 nF capacitor लगाएँ।

## Build कैसे करें

[MPLAB XC8](https://www.microchip.com/xc8) compiler ज़रूरी है।

**MPLAB X IDE:** device `PIC16F877A` और XC8 compiler के साथ नया standalone
project बनाएँ, उसमें `main.c` जोड़ें, फिर Build करें।

**Command line:**

```sh
make
```

इससे `build/main.hex` बनेगी। इसे PICkit 3/4/5 से chip में flash करें, या
simulation के लिए Proteus/SimulIDE में load करें।

## Crystal या LED pin बदलना

- दूसरा crystal: `main.c` में `_XTAL_FREQ` बदलें (4 MHz या कम के crystal के लिए `FOSC = XT` लिखें)।
- दूसरा LED pin: `LED_TRIS` और `LED` define बदलें, जैसे `TRISDbits.TRISD0` / `PORTDbits.RD0`।
- दूसरा बटन pin: `BTN_TRIS` और `BTN` define बदलें। Internal pull-up सिर्फ़ PORTB पर है, इसलिए
  किसी और port पर बटन लगाएँ तो pin से +5 V तक 10 kΩ resistor लगाएँ।
