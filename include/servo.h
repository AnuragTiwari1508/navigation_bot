#ifndef SERVO_H_
#define SERVO_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Servo motor pin (using Timer0 PWM)
#define SERVO_PORT      PORTB
#define SERVO_DDR       DDRB
#define SERVO_PIN       PB3     // OC0 pin for PWM

// Servo positions in degrees
#define SERVO_CENTER    90
#define SERVO_RIGHT     0
#define SERVO_LEFT      180

// PWM values for servo positions (for 50Hz PWM)
#define PWM_CENTER      188     // 1.5ms pulse width
#define PWM_RIGHT       125     // 1.0ms pulse width  
#define PWM_LEFT        250     // 2.0ms pulse width

// Function prototypes
void servo_init(void);
void servo_set_angle(uint8_t angle);
void servo_scan_right(void);
void servo_scan_left(void);
void servo_center(void);

#endif /* SERVO_H_ */