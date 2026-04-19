/*
 * PWM_Manual.c
 *
 * Created: 16/04/2026 03:00:14
 *  Author: Diego
 */ 
#include "PWM_Manual.h"
#include <avr/io.h>
volatile uint8_t PWM_COUNTER;
volatile uint8_t PWM_Manual_VALUE;

/****************************************/
// Interrupt routines
ISR(TIMER2_OVF_vect){
	PWM_COUNTER ++; //Aumenta el contador
	if (PWM_COUNTER>=64) 
	{
		PWM_COUNTER=0; //Sí es mayor o igual a 64 lo reinicia
	}
	if (PWM_COUNTER<PWM_Manual_VALUE)
	{
		PORTD |= (1<<PORTD7); //Si el contador es menor al valor de PWM, enciende PORTD7
	}
	else
	{
		PORTD &= ~(1<<PORTD7); //Si no, apaga PORTD7
	}
}