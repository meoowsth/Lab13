/*	Author: Tinghui Song
 *  Partner(s) Name: 
 *	Lab Section: 24
 *	Assignment: Lab #13  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	Demo link: https://drive.google.com/file/d/1uioLy-gRwX05Bm1TZqXQg1BJZGGSYYrf/view?usp=sharing
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


void ADC_init(){
	ADCSRA |= (1 << ADEN) | ( 1 << ADSC) | ( 1 << ADATE);
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

    /* Insert your solution below */
	ADC_init();

	//unsigned tempA = 0x00;	
	unsigned tempB = 0x00;
	unsigned tempD = 0x00;
	unsigned short x;
	

   	while (1) {
		//tempA = PINA;
		x = ADC;
		tempB = (char)x;
		tempD = (char)(x >> 8);
		PORTB = tempB;
		PORTD = tempD;
  	}
    	return 1;
}
