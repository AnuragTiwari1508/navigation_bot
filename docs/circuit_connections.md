# ATmega32 Navigation Bot - Complete Circuit Diagram

## 🔌 **Complete Wiring Connections**

### **ATmega32 Pinout और Connections:**

```
                    ATmega32 (40-pin DIP)
                    ┌─────────────────────┐
        Reset   1 ──┤ RESET         VCC ├── 40  +5V
        RXD     2 ──┤ PD0           PA0 ├── 39  → Left Motor IN1
        TXD     3 ──┤ PD1           PA1 ├── 38  → Left Motor IN2  
        INT0    4 ──┤ PD2           PA2 ├── 37  → Left Motor EN
        INT1    5 ──┤ PD3           PA3 ├── 36  → Right Motor IN3
        LCD_D4  6 ──┤ PD4           PA4 ├── 35  → Right Motor IN4
        LCD_D5  7 ──┤ PD5           PA5 ├── 34  → Right Motor EN
        LCD_D6  8 ──┤ PD6           PA6 ├── 33  → LED
        LCD_D7  9 ──┤ PD7           PA7 ├── 32  (Not Used)
        XTAL2  10 ──┤ XTAL2         AREF├── 31  → +5V
        XTAL1  11 ──┤ XTAL1         GND ├── 30  → GND
        LCD_RS 12 ──┤ PB0           PC7 ├── 29  (Not Used)
        LCD_EN 13 ──┤ PB1           PC6 ├── 28  (Not Used)
        SS     14 ──┤ PB2           PC5 ├── 27  (Not Used)
      Servo_PWM 15 ──┤ PB3 (OC0)     PC4 ├── 26  (Not Used)
        MOSI   16 ──┤ PB4           PC3 ├── 25  (Not Used)
        MISO   17 ──┤ PB5           PC2 ├── 24  (Not Used)
        SCK    18 ──┤ PB6           PC1 ├── 23  → US Echo
               19 ──┤ PB7           PC0 ├── 22  → US Trigger
        GND    20 ──┤ GND           GND ├── 21  → GND
                    └─────────────────────┘
```

## 🔋 **Power Supply Circuit**

### **Main Power Distribution:**
```
12V DC Input → 7805 Regulator → 5V Output
    │              │              │
    │              │              ├── ATmega32 VCC (Pin 40)
    │              │              ├── LCD VDD
    │              │              ├── Servo Red Wire
    │              │              └── Pull-up Resistors
    │              │
    │              ├── 1000µF Capacitor → GND
    │              └── 100µF Capacitor → GND
    │
    └── L298N Motor Driver VIN
```

## 🖥️ **16x2 LCD Connections (4-bit Mode)**

```
LCD Pin    →    ATmega32 Pin    →    Function
─────────────────────────────────────────────
VSS (1)    →    GND             →    Ground
VDD (2)    →    +5V             →    Power
V0  (3)    →    GND (Direct)    →    Contrast (No Pot needed)
RS  (4)    →    PB0 (Pin 12)    →    Register Select
EN  (5)    →    PB1 (Pin 13)    →    Enable
D4  (11)   →    PD4 (Pin 6)     →    Data Bit 4
D5  (12)   →    PD5 (Pin 7)     →    Data Bit 5
D6  (13)   →    PD6 (Pin 8)     →    Data Bit 6
D7  (14)   →    PD7 (Pin 9)     →    Data Bit 7
A   (15)   →    +5V             →    Backlight Anode
K   (16)   →    GND             →    Backlight Cathode
```

## 📡 **HC-SR04 Ultrasonic Sensor**

```
HC-SR04 Pin  →  ATmega32 Pin    →  Function
──────────────────────────────────────────
VCC          →  +5V             →  Power
GND          →  GND             →  Ground  
Trig         →  PC0 (Pin 22)    →  Trigger Output
Echo         →  PC1 (Pin 23)    →  Echo Input
```

## 🎛️ **SG90 Servo Motor**

```
Servo Wire   →  Connection       →  Function
──────────────────────────────────────────
Red          →  +5V             →  Power
Brown/Black  →  GND             →  Ground
Orange/Yellow→  PB3 (Pin 15)    →  PWM Signal (OC0)
```

## 🚗 **L298N Motor Driver Module**

```
L298N Pin    →  Connection       →  Function
──────────────────────────────────────────
VCC          →  +5V (Logic)     →  Logic Power
GND          →  GND             →  Common Ground
VIN          →  +12V            →  Motor Power
ENA          →  PA2 (Pin 37)    →  Left Motor Enable
IN1          →  PA0 (Pin 39)    →  Left Motor Direction 1
IN2          →  PA1 (Pin 38)    →  Left Motor Direction 2
IN3          →  PA3 (Pin 36)    →  Right Motor Direction 1
IN4          →  PA4 (Pin 35)    →  Right Motor Direction 2
ENB          →  PA5 (Pin 34)    →  Right Motor Enable
```

## 💡 **LED Indicator**

```
Component    →  Connection       →  Function
──────────────────────────────────────────
LED Anode    →  220Ω → PA6      →  Obstacle Indicator
LED Cathode  →  GND             →  Ground
```

## 🔌 **ISP Programming Header (USBasp)**

```
ISP Pin      →  ATmega32 Pin    →  Function
──────────────────────────────────────────
MISO         →  PB5 (Pin 17)    →  Master In Slave Out
MOSI         →  PB4 (Pin 16)    →  Master Out Slave In  
SCK          →  PB6 (Pin 18)    →  Serial Clock
RESET        →  RESET (Pin 1)   →  Reset (via 10kΩ resistor)
VCC          →  +5V             →  Power
GND          →  GND             →  Ground
```