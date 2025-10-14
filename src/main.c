/*
 * Navigation Bot - ATmega32 Embedded C Project
 * Features:
 * - Obstacle avoidance using ultrasonic sensor
 * - Servo motor scanning for best path
 * - LCD display for navigation status
 * - LED indicator for obstacle detection
 * - 2cm/sec movement speed
 * - Compatible with Microchip Studio
 * 
 * Author: Navigation Bot Project
 * Target: ATmega32 @ 16MHz
 * Programmer: USBasp
 */

#define F_CPU 16000000UL  // 16MHz crystal oscillator

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>

// Include custom drivers
#include "lcd.h"
#include "ultrasonic.h"
#include "servo.h"
#include "motor.h"

// Navigation constants
#define OBSTACLE_THRESHOLD  20  // 20cm obstacle detection
#define SCAN_DELAY_MS       1000
#define TURN_DURATION_MS    800  // Time to complete 90-degree turn

// Navigation states
typedef enum {
    STATE_FORWARD,
    STATE_OBSTACLE_DETECTED,
    STATE_SCANNING,
    STATE_TURNING,
    STATE_STOPPED
} navigation_state_t;

// Global variables
volatile navigation_state_t current_state = STATE_FORWARD;
volatile uint16_t left_distance = 0;
volatile uint16_t right_distance = 0;
volatile uint8_t turn_direction = 0;  // 0 = right, 1 = left

// Function prototypes
void system_init(void);
void navigation_loop(void);
void scan_surroundings(void);
void decide_direction(void);
void execute_turn(void);
void display_status(char* status);
void display_distance(uint16_t distance);

int main(void) {
    // Initialize all systems
    system_init();
    
    // Display startup message
    lcd_clear();
    lcd_gotoxy(0, 0);
    lcd_string("Navigation Bot");
    lcd_gotoxy(0, 1);
    lcd_string("Initializing...");
    _delay_ms(2000);
    
    lcd_clear();
    lcd_gotoxy(0, 0);
    lcd_string("Status: READY");
    lcd_gotoxy(0, 1);
    lcd_string("Distance: --cm");
    
    // Main navigation loop
    while (1) {
        navigation_loop();
        _delay_ms(50);  // Small delay for system stability
    }
    
    return 0;
}

// Initialize all system components
void system_init(void) {
    // Initialize drivers
    lcd_init();
    ultrasonic_init();
    servo_init();
    motor_init();
    
    // Set servo to center position initially
    servo_center();
    
    // Enable global interrupts
    sei();
    
    // Initial system state
    current_state = STATE_FORWARD;
    led_off();
}

// Main navigation logic
void navigation_loop(void) {
    uint16_t front_distance = 0;
    
    switch (current_state) {
        case STATE_FORWARD:
            // Move forward and check for obstacles
            motor_forward();
            display_status("Moving Forward");
            
            // Get distance from front sensor
            front_distance = ultrasonic_get_distance();
            display_distance(front_distance);
            
            // Check if obstacle detected
            if (is_obstacle_detected(OBSTACLE_THRESHOLD)) {
                // Obstacle detected!
                motor_stop();
                led_on();
                current_state = STATE_OBSTACLE_DETECTED;
                display_status("Obstacle!");
                _delay_ms(500);
            }
            break;
            
        case STATE_OBSTACLE_DETECTED:
            // Stop and prepare for scanning
            motor_stop();
            led_on();
            display_status("Scanning...");
            current_state = STATE_SCANNING;
            break;
            
        case STATE_SCANNING:
            // Scan left and right to find best path
            scan_surroundings();
            decide_direction();
            current_state = STATE_TURNING;
            break;
            
        case STATE_TURNING:
            // Execute the turn
            execute_turn();
            led_off();
            current_state = STATE_FORWARD;
            break;
            
        case STATE_STOPPED:
            // Emergency stop state
            motor_stop();
            led_on();
            display_status("STOPPED");
            break;
            
        default:
            current_state = STATE_FORWARD;
            break;
    }
}

// Scan left and right using servo motor
void scan_surroundings(void) {
    // Center servo first
    servo_center();
    _delay_ms(500);
    
    // Scan right (0 degrees)
    display_status("Scanning Right");
    servo_scan_right();
    _delay_ms(SCAN_DELAY_MS);
    right_distance = ultrasonic_get_distance();
    
    // Return to center
    servo_center();
    _delay_ms(500);
    
    // Scan left (180 degrees)
    display_status("Scanning Left");
    servo_scan_left();
    _delay_ms(SCAN_DELAY_MS);
    left_distance = ultrasonic_get_distance();
    
    // Return to center
    servo_center();
    _delay_ms(500);
}

// Decide which direction to turn based on scan results
void decide_direction(void) {
    char buffer[16];
    
    // Display scan results
    lcd_clear();
    snprintf(buffer, sizeof(buffer), "L:%dcm R:%dcm", left_distance, right_distance);
    lcd_gotoxy(0, 0);
    lcd_string(buffer);
    
    // Decide direction based on distances
    if (left_distance > right_distance) {
        turn_direction = 1;  // Turn left
        lcd_gotoxy(0, 1);
        lcd_string("Turning LEFT");
    } else {
        turn_direction = 0;  // Turn right
        lcd_gotoxy(0, 1);
        lcd_string("Turning RIGHT");
    }
    
    _delay_ms(1000);  // Show decision for 1 second
}

// Execute the turn maneuver
void execute_turn(void) {
    if (turn_direction == 1) {
        // Turn left
        motor_turn_left();
        display_status("Turning LEFT");
    } else {
        // Turn right
        motor_turn_right();
        display_status("Turning RIGHT");
    }
    
    // Execute turn for calculated duration
    _delay_ms(TURN_DURATION_MS);
    
    // Stop turning
    motor_stop();
    _delay_ms(200);
}

// Display status message on LCD first line
void display_status(char* status) {
    lcd_gotoxy(0, 0);
    lcd_string("                ");  // Clear line
    lcd_gotoxy(0, 0);
    lcd_string(status);
}

// Display distance on LCD second line
void display_distance(uint16_t distance) {
    char buffer[16];
    
    if (distance > 999) {
        snprintf(buffer, sizeof(buffer), "Distance: MAX");
    } else {
        snprintf(buffer, sizeof(buffer), "Distance: %dcm", distance);
    }
    
    lcd_gotoxy(0, 1);
    lcd_string("                ");  // Clear line
    lcd_gotoxy(0, 1);
    lcd_string(buffer);
}