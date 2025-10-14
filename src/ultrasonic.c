#include "ultrasonic.h"

// Initialize ultrasonic sensor
void ultrasonic_init(void) {
    // Set TRIG pin as output
    US_TRIG_DDR |= (1 << US_TRIG_PIN);
    US_TRIG_PORT &= ~(1 << US_TRIG_PIN);  // Initially low
    
    // Set ECHO pin as input
    US_ECHO_DDR &= ~(1 << US_ECHO_PIN);
    
    // Initialize Timer1 for time measurement
    // Normal mode, prescaler = 8 (for 16MHz clock = 2MHz timer clock)
    TCCR1A = 0x00;
    TCCR1B = 0x02;  // Prescaler = 8
    TCNT1 = 0;
}

// Get distance in centimeters
uint16_t ultrasonic_get_distance(void) {
    uint16_t pulse_width = 0;
    uint16_t distance = 0;
    uint16_t timeout_counter = 0;
    
    // Send 10us trigger pulse
    US_TRIG_PORT |= (1 << US_TRIG_PIN);
    _delay_us(10);
    US_TRIG_PORT &= ~(1 << US_TRIG_PIN);
    
    // Wait for echo pin to go high (start of echo pulse)
    timeout_counter = 0;
    while (!(US_ECHO_INPUT & (1 << US_ECHO_PIN))) {
        _delay_us(1);
        timeout_counter++;
        if (timeout_counter > MAX_TIMEOUT) {
            return 999;  // Timeout - return max distance
        }
    }
    
    // Start timer
    TCNT1 = 0;
    
    // Wait for echo pin to go low (end of echo pulse)
    timeout_counter = 0;
    while (US_ECHO_INPUT & (1 << US_ECHO_PIN)) {
        _delay_us(1);
        timeout_counter++;
        if (timeout_counter > MAX_TIMEOUT) {
            return 999;  // Timeout - return max distance
        }
    }
    
    // Get pulse width from timer
    pulse_width = TCNT1;
    
    // Calculate distance in cm
    // Formula: Distance = (pulse_width * 0.5 * 343 m/s) / 100
    // With prescaler 8 and 16MHz clock: pulse_width * 0.5 * 34.3 / 200
    // Simplified: pulse_width * 0.08575 ≈ pulse_width / 11.66
    distance = pulse_width / 12;  // Approximation for easier calculation
    
    return distance;
}

// Check if obstacle is detected within threshold
uint8_t is_obstacle_detected(uint16_t threshold_cm) {
    uint16_t distance = ultrasonic_get_distance();
    return (distance <= threshold_cm && distance > 0);
}