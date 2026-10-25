# PIC16F877A LED Blink

Blinks an LED on pin RB0 of a PIC16F877A at 1 Hz (500 ms on, 500 ms off).

## Hardware

| Connection | Detail |
|---|---|
| VDD (pins 11, 32) | +5 V |
| VSS (pins 12, 31) | GND |
| MCLR (pin 1) | 10 kΩ to +5 V |
| OSC1/OSC2 (pins 13, 14) | 20 MHz crystal, 22 pF from each pin to GND |
| RB0 (pin 33) | 330 Ω resistor → LED anode, LED cathode → GND |

Put a 100 nF decoupling capacitor between VDD and VSS close to the chip.

## Build

Requires [MPLAB XC8](https://www.microchip.com/xc8).

**MPLAB X IDE:** create a standalone project for device `PIC16F877A` with the
XC8 compiler, add `main.c`, then build.

**Command line:**

```sh
make
```

This produces `build/main.hex`. Flash it with a PICkit 3/4/5, or load it into
Proteus/SimulIDE to simulate.

## Changing the clock or LED pin

- Different crystal: change `_XTAL_FREQ` in `main.c` (use `FOSC = XT` for crystals of 4 MHz or less).
- Different pin: change the `LED_TRIS` and `LED` defines, e.g. `TRISDbits.TRISD0` / `PORTDbits.RD0`.
