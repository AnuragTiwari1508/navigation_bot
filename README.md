# Navigation Bot - ATmega32 Embedded System

## Project Overview

This is a complete navigation system for ATmega32 microcontroller featuring obstacle avoidance, servo-based scanning, and intelligent pathfinding. The robot moves at 2cm/second and uses an ultrasonic sensor for obstacle detection.

### Features

- **Obstacle Detection**: HC-SR04 ultrasonic sensor with 20cm threshold
- **Smart Navigation**: Servo motor scanning for optimal path selection  
- **Visual Feedback**: 16x2 LCD display showing status and directions
- **LED Indicator**: Lights up when obstacle detected
- **Precise Movement**: 2cm/second movement speed with accurate turning
- **Autonomous Operation**: Fully automated navigation with no user input required

### Hardware Requirements

#### Core Components
- ATmega32 microcontroller (16MHz crystal)
- HC-SR04 ultrasonic sensor
- SG90 servo motor
- 16x2 LCD display (HD44780 compatible)
- L298N motor driver module
- 2x DC geared motors with wheels
- LED indicator
- USBasp programmer

#### Power Supply
- 12V, 2A power adapter for motors
- 7805 voltage regulator for 5V logic supply
- Appropriate capacitors and resistors (see circuit diagram)

### Project Structure

```
navigation_bot/
├── src/
│   ├── main.c          # Main navigation logic
│   ├── lcd.c           # LCD driver functions
│   ├── ultrasonic.c    # Ultrasonic sensor interface
│   ├── servo.c         # Servo motor control
│   └── motor.c         # DC motor control
├── include/
│   ├── lcd.h           # LCD function declarations
│   ├── ultrasonic.h    # Ultrasonic sensor definitions
│   ├── servo.h         # Servo motor definitions
│   └── motor.h         # Motor control definitions
├── docs/
│   └── circuit_diagram.md  # Complete wiring diagram
├── navigation_bot.cproj    # Microchip Studio project file
├── navigation_bot.atsln    # Microchip Studio solution file
├── Makefile               # Command-line build system
└── README.md             # This file
```

## Getting Started

### Step 1: Hardware Assembly

1. **Build the circuit** according to `docs/circuit_diagram.md`
2. **Mount components** on robot chassis:
   - Servo motor on top for 360° scanning
   - Ultrasonic sensor on servo horn
   - LCD display on front panel
   - Motors and wheels on chassis
3. **Connect power supplies**:
   - 12V for motors via L298N
   - 5V for logic circuits via 7805 regulator
4. **Verify all connections** before powering on

### Step 2: Software Setup

#### Option A: Using Microchip Studio (Recommended)

1. **Install Microchip Studio** (formerly Atmel Studio)
2. **Open project**: Double-click `navigation_bot.atsln`
3. **Build project**: Press F7 or Build → Build Solution
4. **Connect USBasp** programmer to ISP header
5. **Program device**: Tools → Device Programming

#### Option B: Using Command Line (Linux/macOS)

1. **Install AVR toolchain**:
   ```bash
   # Ubuntu/Debian
   sudo apt-get install gcc-avr avr-libc avrdude
   
   # macOS with Homebrew
   brew install avr-gcc avrdude
   ```

2. **Build project**:
   ```bash
   make clean
   make all
   ```

3. **Program device**:
   ```bash
   make flash
   make fuses  # Set fuses for 16MHz external crystal
   ```

### Step 3: USBasp Driver Setup (Windows)

#### Install Zadig Driver

1. **Download Zadig** from https://zadig.akeo.ie/
2. **Connect USBasp** to computer
3. **Run Zadig as Administrator**
4. **Select USBasp device** from dropdown
5. **Select libusb-win32 driver**
6. **Click "Replace Driver"**
7. **Wait for installation** to complete

### Step 4: Programming with ProgISP

#### Install and Configure ProgISP

1. **Download ProgISP** from official source
2. **Install and run** ProgISP
3. **Configure settings**:
   - Chip Type: ATmega32
   - Programmer: USBasp
   - Interface: USB
4. **Load hex file**: Browse to `navigation_bot/Release/navigation_bot.hex`
5. **Set fuses**:
   - Low Fuse: 0xFF (16MHz external crystal)
   - High Fuse: 0xC9 (default settings)
6. **Program device**: Click "Auto" for automatic programming

## How It Works

### Navigation Algorithm

1. **Forward Movement**: Robot moves forward at 2cm/second
2. **Obstacle Detection**: Ultrasonic sensor continuously monitors front distance
3. **Emergency Stop**: When obstacle detected within 20cm:
   - Motors stop immediately
   - LED turns on
   - Display shows "Obstacle!"
4. **Scanning Phase**: Servo rotates sensor to scan left and right
5. **Path Selection**: Algorithm chooses direction with greater clearance
6. **Turning**: Robot turns toward selected direction
7. **Resume**: LED turns off, forward movement resumes

### System States

- **STATE_FORWARD**: Normal forward movement
- **STATE_OBSTACLE_DETECTED**: Obstacle found, preparing to scan
- **STATE_SCANNING**: Servo scanning left/right for best path
- **STATE_TURNING**: Executing turn maneuver
- **STATE_STOPPED**: Emergency stop condition

### Display Information

- **Line 1**: Current status (Moving Forward, Scanning, Turning)
- **Line 2**: Distance reading or turn direction

## Troubleshooting

### Common Issues

#### Programming Problems
- **USBasp not detected**: Install proper drivers using Zadig
- **Device not responding**: Check ISP connections and power
- **Fuse settings**: Ensure correct fuses for 16MHz crystal

#### Hardware Issues
- **LCD not displaying**: Check 4-bit wiring and contrast
- **Motors not moving**: Verify L298N connections and power supply
- **Erratic servo**: Check PWM signal and power supply stability
- **Sensor not reading**: Verify trigger/echo pin connections

#### Software Issues
- **Compilation errors**: Check include paths and file locations
- **Runtime crashes**: Verify crystal frequency and fuse settings

### Debugging Tips

1. **Start simple**: Test each component individually
2. **Check power**: Ensure stable 5V and 12V supplies
3. **Use multimeter**: Verify pin voltages and connections
4. **Serial debug**: Add UART output for debugging (optional)

## Customization

### Adjusting Movement Speed

Edit `motor.h` and modify:
```c
#define MOTOR_SPEED_FORWARD 150  // Adjust for desired speed
#define TURN_DURATION_MS    800  // Adjust turn timing
```

### Changing Detection Threshold

Edit `main.c` and modify:
```c
#define OBSTACLE_THRESHOLD  20  // Distance in cm
```

### LCD Messages

Customize display messages in `main.c`:
```c
display_status("Your Message");
```

## Pin Configuration Summary

| Component | ATmega32 Pin | Function |
|-----------|--------------|----------|
| LCD RS | PB0 | Register Select |
| LCD EN | PB1 | Enable |
| LCD D4-D7 | PD4-PD7 | Data Lines |
| Servo PWM | PB3 (OC0) | PWM Control |
| US Trigger | PC0 | Trigger Pulse |
| US Echo | PC1 | Echo Input |
| Left Motor | PA0-PA2 | Control + Enable |
| Right Motor | PA3-PA5 | Control + Enable |
| LED | PA6 | Status Indicator |

