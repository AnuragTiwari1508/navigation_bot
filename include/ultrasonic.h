#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Ultrasonic sensor pins
#define US_TRIG_PORT    PORTC
#define US_TRIG_DDR     DDRC
#define US_TRIG_PIN     PC0

#define US_ECHO_PORT    PORTC
#define US_ECHO_DDR     DDRC
#define US_ECHO_PIN     PC1
#define US_ECHO_INPUT   PINC

// Timer settings for distance measurement
#define TIMER_PRESCALER 8
#define MAX_TIMEOUT     65000

// Function prototypes
void ultrasonic_init(void);
uint16_t ultrasonic_get_distance(void);
uint8_t is_obstacle_detected(uint16_t threshold_cm);

#endif /* ULTRASONIC_H_ */