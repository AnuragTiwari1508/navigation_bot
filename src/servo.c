#include "servo.h"

// Initialize servo motor (Timer0 PWM)
void servo_init(void) {
    // Set servo pin as output
    SERVO_DDR |= (1 << SERVO_PIN);
    
    // Configure Timer0 for Fast PWM mode
    // WGM01:WGM00 = 11 (Fast PWM)
    // COM01:COM00 = 10 (Clear OC0 on compare match, set at BOTTOM)
    TCCR0 = (1 << WGM01) | (1 << WGM00) | (1 << COM01) | (1 << CS02) | (1 << CS00);
    
    // Set prescaler to 1024 for 50Hz PWM (16MHz / 1024 / 256 ≈ 61Hz)
    // This gives us approximately 50Hz which is suitable for servo control
    
    // Set initial position to center
    OCR0 = PWM_CENTER;
    
    _delay_ms(500);  // Allow servo to reach initial position
}

// Set servo angle (0-180 degrees)
void servo_set_angle(uint8_t angle) {
    uint8_t pwm_value;
    
    // Limit angle to valid range
    if (angle > 180) angle = 180;
    
    // Convert angle to PWM value
    // Linear interpolation: PWM = PWM_RIGHT + (angle * (PWM_LEFT - PWM_RIGHT) / 180)
    pwm_value = PWM_RIGHT + ((uint16_t)angle * (PWM_LEFT - PWM_RIGHT)) / 180;
    
    OCR0 = pwm_value;
    _delay_ms(300);  // Give servo time to move
}

// Scan servo to right (0 degrees)
void servo_scan_right(void) {
    servo_set_angle(SERVO_RIGHT);
    _delay_ms(500);  // Wait for servo to reach position
}

// Scan servo to left (180 degrees)  
void servo_scan_left(void) {
    servo_set_angle(SERVO_LEFT);
    _delay_ms(500);  // Wait for servo to reach position
}

// Move servo to center position (90 degrees)
void servo_center(void) {
    servo_set_angle(SERVO_CENTER);
    _delay_ms(500);  // Wait for servo to reach position
}