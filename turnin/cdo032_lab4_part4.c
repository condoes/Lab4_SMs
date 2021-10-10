/*	Author: Cindy Do
 *  Partner(s) Name: 
 *	Lab Section: 23
 *	Assignment: Lab #4  Exercise #4
 *	Exercise Description: 
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {start, locked, PA2_Pressed, PA2_Released, error, Y_Pressed, unlocked, lock2 } State;

void Tick() {
    unsigned char tmpA = 0x0;
    switch (State)
    {
    case start: 
        State = locked;
        break;

    case locked:
        PORTB = 0;
        tmpA = PINA & 0x07;
        if(tmpA == 0x04) {
            State = PA2_Pressed;
        }
        else if (tmpA == 0){
            State = locked;
        }
        else {
            State = error;
        }
        break;

    case PA2_Pressed:
        tmpA = PINA & 0x07;
        if(tmpA == 0x04) {
            State = PA2_Pressed;
        }
        else if(tmpA == 0){
            State = PA2_Released;
        }
        else {
            State = error;
        }
        break;

    case PA2_Released:
        tmpA = PINA & 0x07;
        if(tmpA == 0x02) {
            State = Y_Pressed;
        }
        else if(tmpA == 0) {
            State = PA2_Released;
        }
        else {
            State = error;
        }
        break;

    case Y_Pressed:
        tmpA = PINA & 0x07;
        if(tmpA == 0x02) {
            State = Y_Pressed;
        }
        else if(tmpA == 0) {
            PORTB = 1;
            State = unlocked;
        } 
        else if(PORTB == 1) {
            State = locked;
        }
        else {
            State = error;
        }
        break;

    case unlocked: 
        PORTB = 0x01;
        if(PINA == 0x80) {
            State = locked;
        }
        else if(PINA == 0x04) {
            State = lock2;
        }
        else {
            State = unlocked;      
        }
        break;

    case error:
        tmpA = PINA & 0x07;
        if(tmpA == 0) {
            State = locked;
        }
        else {
            State = error;
        }
        break;

    case lock2: 
        if(PINA == 4) {
            State = PA2_Pressed;
        }
        
    
    default:
        State = start;
        break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
    while (1) {
        Tick();
    }
    return 1;
}
