/*
 * PWM1.c
 *
 * Created: 11/04/2026 23:46:51
 *  Author: Diego
 */ 
#include "PWM0A.h"
#include <avr/io.h>
void PWM0A(uint8_t modo, int prescaler, uint8_t invert)
{
	DDRD |= (1<<DDD6); //Enciende el puerto correspondiente
	if (invert == invertido) //Configura si está o no invertido
	{
		TCCR0A &= ~((1<<COM0A0) | (1<<COM0A1));
		TCCR0A |= (1<<COM0A0) | (1<<COM0A1);
	} else {
		TCCR0A &= ~((1<<COM0A0) | (1<<COM0A1));
		TCCR0A |= (1<<COM0A1); //De forma predeterminada está en no invertido
	}
	if (modo == phase_correct) //Configura el modo
	{
		TCCR0A &= ~((1<<WGM01) | (1<<WGM00));
		TCCR0A |= (1<<WGM00);
	} 
	else
	{
		TCCR0A &= ~((1<<WGM01) | (1<<WGM00));
		TCCR0A |= (1<<WGM00) | (1<<WGM01); //De forma predeterminada está en fast
	}
	switch (prescaler) {	//Configura el prescaler
	case 8:
	TCCR0B &= ~((1<<CS02) | (1<<CS01) | (1<<CS00));
	TCCR0B |= (1<<CS01);
	break;
	case 64:
	TCCR0B &= ~((1<<CS02) | (1<<CS01) | (1<<CS00));
	TCCR0B |= (1<<CS01) | (1<<CS00);
	break;
	case 256:
	TCCR0B &= ~((1<<CS02) | (1<<CS01) | (1<<CS00));
	TCCR0B |= (1<<CS02);
	break;
	case 1024:
	TCCR0B &= ~((1<<CS02) | (1<<CS01) | (1<<CS00));
	TCCR0B |= (1<<CS02) | (1<<CS00);
	break;
	default:
	TCCR0B &= ~((1<<CS02) | (1<<CS01) | (1<<CS00));
	TCCR0B |= (1<<CS00);	//Prescaler de 1 predeterminado
	break;
	}
}