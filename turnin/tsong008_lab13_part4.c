/*	Author: Tinghui Song
 *  Partner(s) Name: 
 *	Lab Section: 24
 *	Assignment: Lab #13  Exercise #4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	Demo link: https://drive.google.com/file/d/1G3BysPuKyfJV7LPyBraDBe3g4jm-UsoF/view?usp=sharing
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include <math.h>
#include "Timer.h"

unsigned char pattern;
unsigned char row;

unsigned short hor;
unsigned short ver;
unsigned int d;

void A2D_init(){
 	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1 << ADATE);
}

void Set_A2D_Pin(unsigned char pinNum){
 	ADMUX = (pinNum <= 0x07) ? pinNum : ADMUX;

 static unsigned char i = 0;
 	for(i = 0; i < 15; i++){ asm("nop");}
}

void Tick(){
	 if(hor >= 0x0223){
	   if(pattern > 0x01 ){
	     pattern >>= 1;
	   }
	 }
	 else if(hor <= 0x01D8){
	   if(pattern  < 0x80){
	     pattern <<= 1;
	   }
	 }
	 if(ver <= 0x01D8){
	   if(row > 0x03){
	     row <<= 1;
	   }
	 }
	 else if(ver >= 0x0228){
	   if(row < 0x20){
	     row >>= 1;
	   }
	 }
	}
//--------------------------------------
// LED Matrix Demo SynchSM
// Period: 100 ms
//--------------------------------------
enum States {Start, Wait} State;
void Tick() {
	 Set_A2D_Pin(0x00);
	 ver = ADC;

	 Set_A2D_Pin(0x01);
	 hor = ADC;

	 d = (int)(sqrt(pow((hor - 410), 2)  +  pow((ver - 410), 2)));

	 switch(State){
	   case Start:
	     pattern = 0x08;
	     row = 0x20;
	     State = Wait;
	     break;
	   case Wait:
	     if(d >= 0x0040){
	       Tick();
	     }
	     State = Wait;
	     break;
	   default:
	     State = Wait;
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
	   TimerSet(500);
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

