#define F_CPU 16000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>


volatile char flag = 0;

// this program controls a servo motor using a rotary encoder

ISR(INT0_vect){
    flag = 1;
}


int main(void)
{
    cli();

    unsigned char offset = 128;
    // falling edge interrupt
    EICRA |= 1 << ISC01;
    // enable ext0 interrupt
    EIMSK |= 1 << INT0;

    // setup encoder pins
    DDRD &= ~(1 << PD0 | 1 << PD2);
    PORTD &= ~(1 << PD0 | 1 << PD2);
    
    
    // setup pwm on timer 1 for the servo motor
    DDRB |= 1 << PB1;
    PRR &= ~(1 << PRTIM1);
    OCR1A = 2000 + offset*8;
    ICR1 = 39999;
    TCCR1A |= 1 << COM1A1 | 1 << WGM11;
    TCCR1B |= 1 << WGM13 | 1 << WGM12 | 1 << CS11;

    sei();
    while(1){
	if(flag){
	   if (PIND&(1<<PD0))
	       offset += 20;
	   else
	       offset -= 20;
	   OCR1A = 2000 + offset * 8;
	   flag = 0;
	}
    }
    return 0;
}
