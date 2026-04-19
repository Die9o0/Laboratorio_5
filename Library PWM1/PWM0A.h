/*
 * PWM1.h
 *
 * Created: 11/04/2026 23:43:48
 *  Author: Diego
 */ 
#include <avr/io.h>
#ifndef PWM0A_H_
#define PWM0A_H_
#define fast 1
#define phase_correct 0
#define no_invertido 1
#define invertido 0
void PWM0A(uint8_t modo, int prescaler, uint8_t  invert);

#endif /* PWM0A_H_ */