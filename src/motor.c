#include "motor.h"

// Initialize motor pins and LED
void motor_init(void) {
    // Set motor control pins as output
    LEFT_MOTOR_DDR |= (1 << LEFT_MOTOR_IN1) | (1 << LEFT_MOTOR_IN2) | (1 << LEFT_MOTOR_EN);
    RIGHT_MOTOR_DDR |= (1 << RIGHT_MOTOR_IN3) | (1 << RIGHT_MOTOR_IN4) | (1 << RIGHT_MOTOR_EN);
    
    // Set LED pin as output
    LED_DDR |= (1 << LED_PIN);
    
    // Initialize all pins to low
    LEFT_MOTOR_PORT &= ~((1 << LEFT_MOTOR_IN1) | (1 << LEFT_MOTOR_IN2));
    RIGHT_MOTOR_PORT &= ~((1 << RIGHT_MOTOR_IN3) | (1 << RIGHT_MOTOR_IN4));
    
    // Enable motors (active high)
    LEFT_MOTOR_PORT |= (1 << LEFT_MOTOR_EN);
    RIGHT_MOTOR_PORT |= (1 << RIGHT_MOTOR_EN);
    
    // LED off initially
    LED_PORT &= ~(1 << LED_PIN);
}

// Move forward at 2cm/sec speed
void motor_forward(void) {
    // Left motor forward
    LEFT_MOTOR_PORT |= (1 << LEFT_MOTOR_IN1);
    LEFT_MOTOR_PORT &= ~(1 << LEFT_MOTOR_IN2);
    
    // Right motor forward
    RIGHT_MOTOR_PORT |= (1 << RIGHT_MOTOR_IN3);
    RIGHT_MOTOR_PORT &= ~(1 << RIGHT_MOTOR_IN4);
}

// Move backward
void motor_backward(void) {
    // Left motor backward
    LEFT_MOTOR_PORT &= ~(1 << LEFT_MOTOR_IN1);
    LEFT_MOTOR_PORT |= (1 << LEFT_MOTOR_IN2);
    
    // Right motor backward
    RIGHT_MOTOR_PORT &= ~(1 << RIGHT_MOTOR_IN3);
    RIGHT_MOTOR_PORT |= (1 << RIGHT_MOTOR_IN4);
}

// Turn left (right motor forward, left motor stop/slow)
void motor_turn_left(void) {
    // Left motor stop
    LEFT_MOTOR_PORT &= ~((1 << LEFT_MOTOR_IN1) | (1 << LEFT_MOTOR_IN2));
    
    // Right motor forward
    RIGHT_MOTOR_PORT |= (1 << RIGHT_MOTOR_IN3);
    RIGHT_MOTOR_PORT &= ~(1 << RIGHT_MOTOR_IN4);
}

// Turn right (left motor forward, right motor stop/slow)
void motor_turn_right(void) {
    // Left motor forward
    LEFT_MOTOR_PORT |= (1 << LEFT_MOTOR_IN1);
    LEFT_MOTOR_PORT &= ~(1 << LEFT_MOTOR_IN2);
    
    // Right motor stop
    RIGHT_MOTOR_PORT &= ~((1 << RIGHT_MOTOR_IN3) | (1 << RIGHT_MOTOR_IN4));
}

// Stop both motors
void motor_stop(void) {
    // Stop left motor
    LEFT_MOTOR_PORT &= ~((1 << LEFT_MOTOR_IN1) | (1 << LEFT_MOTOR_IN2));
    
    // Stop right motor
    RIGHT_MOTOR_PORT &= ~((1 << RIGHT_MOTOR_IN3) | (1 << RIGHT_MOTOR_IN4));
}

// Turn LED on
void led_on(void) {
    LED_PORT |= (1 << LED_PIN);
}

// Turn LED off
void led_off(void) {
    LED_PORT &= ~(1 << LED_PIN);
}

// Calculate delay for specific distance at 2cm/sec
void delay_for_distance(uint16_t distance_cm) {
    // At 2cm/sec, time = distance / speed
    // For distance in cm: time in seconds = distance_cm / 2
    // Convert to milliseconds: time_ms = (distance_cm * 1000) / 2 = distance_cm * 500
    uint16_t delay_ms = distance_cm * 500;
    
    // Break into smaller delays to avoid overflow
    while (delay_ms > 1000) {
        _delay_ms(1000);
        delay_ms -= 1000;
    }
    
    if (delay_ms > 0) {
        _delay_ms(delay_ms);
    }
}