/*	Author: Cindy Do
 *  Partner(s) Name: 
 *	Lab Section: 23
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description: PB0 and PB1 each connect to an LED, and PB0's LED is initially on. Pressing a button connected to PA0 turns off PB0's LED and turns on PB1's LED, staying that way after button release. Pressing the button again turns off PB1's LED and turns on PB0's LED. 
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States { Start, init, incr, decr, reset } State;

void Tick() {
	
    switch(State) {
        case Start:
            PORTC = 0x07;
            State = init;
            break;

        case init: 
            if(PINA == 0x2) {
                State = decr;
                if(PORTC > 0) {
                    PORTC = PORTC - 1;
                }
            }
            if(PINA == 0x3){
                State = reset;
                PORTC = 0x0;
            }
            if(PINA == 0x1) {    
                State = incr;
                if(PORTC < 9) {
                    PORTC = PORTC + 1;
                }
            }
            if(PINA == 0) {
                State = init;
            }     
            break;

        case incr: 
            if(PINA == 0x3) {
                State = reset;
                PORTC = 0x0;
            }
            if(PINA == 0x2) {
                State = decr;
                if(PORTC > 0) {
                    PORTC = PORTC - 1;
                }
            }
            if(PINA == 0){
                State = init;
            }
            break;

        case decr: 
            if(PINA == 0x3) {
                State = reset;
                PORTC = 0x0;
            }
            if(PINA == 0x1) {
                State = incr;
                if(PORTC < 9) {
                    PORTC = PORTC + 1;
                }
            }
            if(PINA == 0){
                State = init;
            }           
            break;

        case reset: 
            if(PINA == 0x1) {  
                State = incr;
                PORTC = PORTC + 1;
            }
            if(PINA == 0x2) {
                State = decr;
            }
            if(PINA == 0){
                State = init;
            }   
            break;

        default: 
            State = Start;
            break; 
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    /* Insert your solution below */
    while (1) {
        Tick();
    }
    return 1;
}