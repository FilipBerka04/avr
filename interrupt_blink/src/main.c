#include <avr/io.h>
#define F_CPU 16000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/power.h>

// this programs uses a timer interrupt to toggle the internal led pin

ISR(TIMER1_COMPA_vect)
{
    // set the pin
    PINB |= 1 << PB5;
}

int main(void)
{
    sei();
    // set pin as output
    DDRB |= 1 << PB5;

    // setup the timer
    PRR &= ~(1 << PRTIM1);
    TCCR1B |= 1 << WGM12 | 1 << CS12;
    OCR1A = 31249;
    TIMSK1 |= 1 << OCIE1A;

    while (1)
        ;
    return 0;
}
