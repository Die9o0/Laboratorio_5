/*
 * Laboratorio 5.c
 *
 * Created: 11/04/2026
 * Author: Diego Camey
 * Description: PWM y librerías
 */
/****************************************/
// Encabezado (Libraries)
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000
#include <util/delay.h>
#include <stdbool.h>
#include "Library PWM1/PWM0A.h"
#include "Library PWM1/PWM0B.h"
#include "Library PWM1/PWM_Manual.h"
/****************************************/
// Function prototypes
void setup();
void initADC();
void initTMR2();
/****************************************/
// Variables y constantes
volatile uint8_t Lectura_ADC_1;
volatile uint8_t Lectura_ADC_2;
volatile uint8_t Lectura_ADC_3;
volatile uint8_t ADC_FLAG;
#define TMR2_VALUE 100;
/****************************************/
// Main Function
int main(void)
{
	//Setup
	cli();
	setup();
	initADC();
	initTMR2();
	ADCSRA	|= (1<<ADSC) | (1<<ADIE);
	ADC_FLAG = 0;
	sei();
	while (1)
	{
		OCR0A = (0.0612745*Lectura_ADC_3)+14.6249984; //Mapea el valor del ADC a OCR0A correspondiente para el ángulo del servo
		OCR0B = (0.0612745*Lectura_ADC_2)+14.6249984; //Mapea el valor del ADC a OCR0B correspondiente para el ángulo del servo
		PWM_Manual_VALUE = (Lectura_ADC_1)/4;	//Cambia el valor que cumple la función de OCRnx
	}
}
/****************************************/
// NON-Interrupt subroutines
void setup(){
	//Sistema a 1MHz
	CLKPR	= (1<<CLKPCE);
	CLKPR	= (1<<CLKPS2);
	PWM0A(fast, 64, no_invertido);	//Llama a la función de configuración
	PWM0B(fast, 64, no_invertido);	//Llama a la función de configuración
	DDRC = 0x00;	
	DDRD |= (1<<DDD7);	//Entradas y salidas
}
void initADC()
{
	//Aref = AVcc; Izquierda; ADC6
	ADMUX	= 0;
	ADMUX	|= (1<<REFS0) |  (1<<ADLAR) | (1<<MUX2) | (1<<MUX1);
	//Habilitar ADC y prescaler de 16
	ADCSRA	= (1<<ADEN) | (1<<ADPS2);
}
void initTMR2()
{
	TCCR2A = 0;
	TCCR2B = 0;
	TCCR2B |= (1 << CS00); //Prescaler de 1
	TIMSK2 = (1 << TOIE2); //Interrupciones
}
/****************************************/
// Interrupt routines
ISR(ADC_vect){
	switch (ADC_FLAG){
		case 0:ADMUX &= ~((1<<MUX0) | (1<<MUX1) | (1<<MUX2)); //Apaga el MUX
		ADMUX |= (1<<MUX0)	| (1<<MUX1) | (1<<MUX2); //Enciende mux 6
		Lectura_ADC_1 = ADCH; //Guarda la lectura
		break;
		case 1:
		ADMUX &= ~((1<<MUX0) | (1<<MUX1) | (1<<MUX2)); 
		ADMUX |= (1<<MUX1) | (1<<MUX2);
		Lectura_ADC_2 = ADCH;
		break;
		case 2:
		ADMUX &= ~((1<<MUX0) | (1<<MUX1) | (1<<MUX2));
		ADMUX |= (1<<MUX0) | (1<<MUX2);
		Lectura_ADC_3 = ADCH;
		break;
	}
	ADCSRA	|= (1<<ADSC); //Lee de nuevo
	ADC_FLAG ++;	//Aumenta el contador del MUX
	if (ADC_FLAG==3) //Reinicia el contador del MUX
	{
		ADC_FLAG=0;
	}
}
