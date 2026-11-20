#define F_CPU 16000000UL

#include <avr/power.h>
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    // timer goes BOTTOM -> TOP -> BOTTOM -> ...
    // the output pin turns on when timer gets cleared
    // the output pin turns off  when timer passes the OCR1A
    // 
    // prescaler 64
    // top + 1	 5000
    
    // set the pin b1 to output
    DDRB |= 1 << PB1;
    // enable timer 1
    PRR &= ~(1 << PRTIM1);
    // set the value of the Output Compare Register A
    OCR1A = 250;
    // set the value of ICR1 (TOP)
    ICR1 = 4999;
    // select the non inverting mode of pwm
    TCCR1A |= 1 << COM1A1;
    // choose the fast PWM TOP = ICR1
    TCCR1A |= 1 << WGM11;
    TCCR1B |= 1 << WGM13 | 1 << WGM12;

    // choose the /64 prescaler (this starts the timer)
    TCCR1B |= 3;
    while(1){
	_delay_ms(1000);
	OCR1A = 300;
	_delay_ms(1000);
	OCR1A = 400;
    }

    return 0;
}
