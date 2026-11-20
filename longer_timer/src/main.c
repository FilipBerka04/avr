#define F_CPU 16000000UL

#include <avr/power.h>
#include <avr/io.h>

int main(void)
{
    // set the pin b1 to output
    DDRB |= 1 << PB1;
    // enable timer 1
    PRR &= ~(1 << PRTIM1);
    // set the value of the Output Compare Register A
    OCR1A = 62500;
    // setu the compare output mode A to toggle on match
    TCCR1A |= 1 << COM1A0;
    // choose the CTC mode
    TCCR1B |= (1 << WGM12);
    // choose the /256 prescaler (this starts the timer)
    TCCR1B |= 4;
    while(1);

    return 0;
}
