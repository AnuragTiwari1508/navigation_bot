#ifndef MOTOR_H_
#define MOTOR_H_

#include <avr/io.h>
#include <util/delay.h>

// Motor Driver Pins (L298N or similar)
// Left Motor
#define LEFT_MOTOR_PORT     PORTA
#define LEFT_MOTOR_DDR      DDRA
#define LEFT_MOTOR_IN1      PA0
#define LEFT_MOTOR_IN2      PA1
#define LEFT_MOTOR_EN       PA2

// Right Motor  
#define RIGHT_MOTOR_PORT    PORTA
#define RIGHT_MOTOR_DDR     DDRA
#define RIGHT_MOTOR_IN3     PA3
#define RIGHT_MOTOR_IN4     PA4
#define RIGHT_MOTOR_EN      PA5

// LED Pin
#define LED_PORT            PORTA
#define LED_DDR             DDRA
#define LED_PIN             PA6

// Motor directions
#define MOTOR_FORWARD       1
#define MOTOR_BACKWARD      2
#define MOTOR_STOP          0

// Motor speeds (for 2cm/sec movement)
#define MOTOR_SPEED_FORWARD 150   // Adjust based on your motor and wheels
#define MOTOR_SPEED_TURN    120   // Slightly slower for turns

// Function prototypes
void motor_init(void);
void motor_forward(void);
void motor_backward(void);
void motor_turn_left(void);
void motor_turn_right(void);
void motor_stop(void);
void led_on(void);
void led_off(void);
void delay_for_distance(uint16_t distance_cm);

#endif /* MOTOR_H_ */