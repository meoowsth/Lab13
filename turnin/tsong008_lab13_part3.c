/*	Author: Tinghui Song
 *  Partner(s) Name: 
 *	Lab Section: 24
 *	Assignment: Lab #13  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	Demo link: https://drive.google.com/file/d/1BQXfyFd5Tw3Z1zMXSBWuDBbTs7kY_U8B/view?usp=sharing
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "Timer.h"

unsigned char pattern;
unsigned char row;

unsigned short x;

void A2D_init(){
	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1 << ADATE);
}

//--------------------------------------
// LED Matrix Demo SynchSM
// Period: 100 ms
//--------------------------------------
enum Demo_States {Start, Wait} State;

void Tick() {
	x = ADC;

	switch(State){
		case Start:
			pattern = 0x08;
			row = 0x01;
			State = Wait;
			break;
		case Wait:
			if (x > 0x0214 && x <= 0x0280) {
				if(pattern == 0x01){
					pattern = 0x80;
				}
				else{
					pattern >>= 1;
				}
				TimerSet(1000);
			}
			else if (x > 0x0280 && x <= 0x0300) {
				if(pattern == 0x01){
					pattern = 0x80;
				}
				else{
					pattern >>= 1;
				}
				TimerSet(500);
			}
			else if (x > 0x0300 && x <= 0x0380) {
				if(pattern == 0x01){
					pattern = 0x80;
				}
				else{
					pattern >>= 1;
				}
				TimerSet(250);
			}
			else if (x > 0x0380 && x <= 0x0400) {
				if(pattern == 0x01){
					pattern = 0x80;
				}
				else{
					pattern >>= 1;
				}
				TimerSet(100);
			}

			else if (x >= 0 && x < 0x0080){
				if(pattern == 0x80){
					pattern = 0x01;
				}
				else{
					pattern <<= 1;
				}
				TimerSet(100);
			}
			else if (x >= 0x0080 && x < 0x0100){
				if(pattern == 0x80){
					pattern = 0x01;
				}
				else{
					pattern <<= 1;
				}
				TimerSet(250);
			}
			else if (x >= 0x0100 && x < 0x0180){
				if(pattern == 0x80){
					pattern = 0x01;
				}
				else{
					pattern <<= 1;
				}
				TimerSet(500);
			}
			else if (x >= 0x0180 && x < 0x01EC){
				if(pattern == 0x80){
					pattern = 0x01;
				}
				else{
					pattern <<= 1;
				}
				TimerSet(1000);
			}
			else {
				TimerSet(50);
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
  	A2D_init();

    while (1) {
	Tick();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
