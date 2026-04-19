/*
 * PWM0B.h
 *
 * Created: 13/04/2026 18:31:15
 *  Author: Diego
 */ 

#include <avr/io.h>
#ifndef PWM0B_H_
#define PWM0B_H_

#define fast 1
#define phase_correct 0
#define no_invertido 1
#define invertido 0
void PWM0B(uint8_t modo, int prescaler, uint8_t  invert);

#endif /* PWM0B_H_ */