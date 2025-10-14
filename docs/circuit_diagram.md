# Navigation Bot - Hardware Circuit Diagram

## ATmega32 Pin Configuration

```
                   ATmega32 (40-pin DIP)
                  ┌─────────────────────┐
    (T0/XCK) PB0  │1                 40 │ PA0 (ADC0)      → Left Motor IN1
    (T1) PB1      │2                 39 │ PA1 (ADC1)      → Left Motor IN2
    (AIN0/INT2) PB2│3                 38 │ PA2 (ADC2)      → Left Motor Enable
    (AIN1/OC0) PB3 │4                 37 │ PA3 (ADC3)      → Right Motor IN3
    (SS) PB4      │5                 36 │ PA4 (ADC4)      → Right Motor IN4
    (MOSI) PB5    │6                 35 │ PA5 (ADC5)      → Right Motor Enable
    (MISO) PB6    │7                 34 │ PA6 (ADC6)      → LED
    (SCK) PB7     │8                 33 │ PA7 (ADC7)      → [Available]
              RST │9                 32 │ AREF           → +5V
              VCC │10                31 │ GND            → Ground
              GND │11                30 │ AVCC           → +5V
            XTAL2 │12                29 │ PC7 (TOSC2)    → [Available]
            XTAL1 │13                28 │ PC6 (TOSC1)    → [Available]
    (RXD) PD0     │14                27 │ PC5 (TDI)      → [Available]
    (TXD) PD1     │15                26 │ PC4 (TDO)      → [Available]
    (INT0) PD2    │16                25 │ PC3 (TMS)      → [Available]
    (INT1) PD3    │17                24 │ PC2 (TCK)      → [Available]
    (OC1B) PD4    │18                23 │ PC1 (SDA)      → US Echo
    (OC1A) PD5    │19                22 │ PC0 (SCL)      → US Trigger
    (ICP1) PD6    │20                21 │ PD7            → LCD D7
                  └─────────────────────┘
```

## Component Connections

### 1. LCD 16x2 Display (4-bit Mode)
```
LCD Pin    ATmega32 Pin    Description
VSS        GND             Ground
VDD        +5V             Power Supply
V0         Middle of 10k   Contrast (no pot needed)
           resistor
RS         PB0             Register Select
Enable     PB1             Enable Signal
D4         PD4             Data Bit 4
D5         PD5             Data Bit 5  
D6         PD6             Data Bit 6
D7         PD7             Data Bit 7
A          +5V (via 220Ω)  Backlight Anode
K          GND             Backlight Cathode
```

### 2. HC-SR04 Ultrasonic Sensor
```
US Pin     ATmega32 Pin    Description
VCC        +5V             Power Supply
GND        GND             Ground
Trig       PC0             Trigger Signal
Echo       PC1             Echo Signal
```

### 3. Servo Motor (SG90)
```
Servo Pin  ATmega32 Pin    Description
Red        +5V             Power Supply
Brown      GND             Ground
Orange     PB3 (OC0)       PWM Control Signal
```

### 4. L298N Motor Driver Module
```
L298N Pin  ATmega32 Pin    Description
VCC        +12V            Motor Power Supply
GND        GND             Common Ground
5V         +5V             Logic Power Supply
ENA        PA2             Left Motor Enable
IN1        PA0             Left Motor Direction 1
IN2        PA1             Left Motor Direction 2
ENB        PA5             Right Motor Enable
IN3        PA3             Right Motor Direction 1  
IN4        PA4             Right Motor Direction 2
```

### 5. DC Motors
```
Connect left DC motor to OUT1 and OUT2 of L298N
Connect right DC motor to OUT3 and OUT4 of L298N
```

### 6. LED Indicator
```
LED Pin    ATmega32 Pin    Description
Anode      PA6 (via 330Ω)  LED Control
Cathode    GND             Ground
```

### 7. Power Supply
```
+12V → L298N VCC (for motors)
+5V  → ATmega32 VCC, LCD VDD, US VCC, Servo Red
GND  → Common ground for all components
```

### 8. Crystal Oscillator (16MHz)
```
XTAL1 (Pin 13) → 16MHz Crystal → XTAL2 (Pin 12)
Add 22pF capacitors from each crystal pin to ground
```

### 9. USBasp Programming Header
```
MOSI (PB5) → USBasp Pin 1
MISO (PB6) → USBasp Pin 9  
SCK (PB7)  → USBasp Pin 7
RST        → USBasp Pin 5
VCC        → USBasp Pin 2
GND        → USBasp Pin 10
```

## Power Requirements

- **Total System**: 12V, 2A minimum
- **Motors**: 12V, 1.5A (via L298N)
- **Logic**: 5V, 500mA (ATmega32, sensors, display)
- **Servo**: 5V, 500mA peak

## Component List

### ICs and Modules
- 1x ATmega32-16PU microcontroller
- 1x L298N motor driver module
- 1x HC-SR04 ultrasonic sensor
- 1x 16x2 LCD display (HD44780)
- 1x SG90 servo motor

### Passive Components
- 1x 16MHz crystal oscillator
- 2x 22pF ceramic capacitors
- 1x 10kΩ resistor (LCD contrast)
- 1x 220Ω resistor (LCD backlight)
- 1x 330Ω resistor (LED current limiting)
- 1x 10kΩ pull-up resistor (Reset)

### Power Supply
- 1x 12V, 2A power adapter
- 1x 7805 voltage regulator (12V to 5V)
- 2x 100μF electrolytic capacitors (regulator)
- 2x 0.1μF ceramic capacitors (decoupling)

### Mechanical
- 1x Robot chassis
- 2x DC geared motors (with wheels)
- 1x Servo motor mounting bracket
- Jumper wires and connectors
- PCB or breadboard for connections

## Assembly Notes

1. **Power Distribution**: Use thick wires for motor power (12V) and separate thin wires for logic (5V)
2. **Ground**: Ensure common ground connection for all components
3. **Servo Mounting**: Mount servo on top of robot for 360° scanning
4. **Sensor Placement**: Mount ultrasonic sensor on servo horn for directional scanning
5. **Display Mounting**: Mount LCD on front panel for easy viewing
6. **Programming**: Use 6-pin ISP header for USBasp connection

## Safety Considerations

- Add fuses for motor and logic power supplies
- Use flyback diodes for DC motors (usually built into L298N)
- Ensure proper heat sinking for voltage regulator
- Check all connections before powering on
- Start testing with lower voltages if possible