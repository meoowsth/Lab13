/*	Author: Tinghui Song
 *  Partner(s) Name: 
 *	Lab Section: 24
 *	Assignment: Lab #13  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	Demo link: https://drive.google.com/file/d/1P3HSbzelz8OVJRstXT80TbaJlIGNJf6z/view?usp=sharing
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "Timer.h"

unsigned short x;

unsigned char tempA;
unsigned char pattern;
unsigned char row;

void ADC_init(){
	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1 << ADATE);
}

//--------------------------------------
// LED Matrix Demo SynchSM
// Period: 100 ms
//--------------------------------------
enum tates {Start, Wait} State;

void Tick() {
	x = ADC;
	switch(State){
		case Start:
			pattern = 0x08;
			row = 0x01;
			State = Wait;
			break;
		case Wait:
			if (x > 0x023C && pattern > 0x01) {
				pattern >>= 1;
			}
      			else if (x < 0x01C2 && pattern < 0x80){
				pattern  <<= 1;
			}
      			else if (x < 0x01C2 && pattern == 0x80){
				pattern  = 0x01;
			}
      			else if (x > 0x023C && pattern == 0x01) {
				pattern = 0x80;
			}
			State = Wait;
			break;
    		default:
      			break;

	}
	PORTC = pattern;
	PORTD = ~row;
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRD = 0xFF; PORTD = 0x00;
	DDRC = 0xFF; PORTC = 0x00;

    /* Insert your solution below */
    TimerSet(300);
  	State = Start;
  	TimerOn();
  	ADC_init();

    while (1) {
  	tempA = ~PINA;
	Tick();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
