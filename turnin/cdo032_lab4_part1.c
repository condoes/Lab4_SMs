/*	Author: Cindy Do
 *  Partner(s) Name: 
 *	Lab Section: 23
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: PB0 and PB1 each connect to an LED, and PB0's LED is initially on. Pressing a button connected to PA0 turns off PB0's LED and turns on PB1's LED, staying that way after button release. Pressing the button again turns off PB1's LED and turns on PB0's LED. 
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States { Start, PB0_on, PB0_off, PB1_on, PB1_off, } State;

void TickFct_LED() {
    switch(State) {
        case Start: //initial transition
            State = PB0_on;
            break;

        case PB0_on:
            if((PINA & 0x1) == 1) {
                State = PB0_on;
            }
            else {
                State = PB0_off;
            }
            break;
        
        case PB0_off:
            if((PINA & 0x1) == 1) {
                State = PB1_on;
            }
            else {
                State = PB0_off;
            }
            break;
        
        case PB1_on:
            if((PINA & 0x1) == 1) {
                State = PB1_on;
            }
            else {
                State = PB1_off;
            }
            break;

        case PB1_off:
            if((PINA & 0x1) == 1) {
                State = PB0_on;
            }
            else {
                State = PB1_off;
            }
            break;

        default:
            State = Start;
            break;
    } //transitions

    switch(State) {
        case Start:
            PORTB = 0x1;
            break;

        case PB0_on:
            PORTB = 0x1;
            break;

        case PB0_off:
            break;
        
        case PB1_on:
            PORTB = 0x2;
            break;

        case PB1_off:
            break;

        default:
            PORTB = 0x1;
            break;
    }

}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
    while (1) {
        TickFct_LED();
    }
    return 1;
}