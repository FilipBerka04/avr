#define F_CPU 16000000UL

#include <avr/power.h>

// output: pb5
// input:  pb4

// set the pin as output
void set_out()
{
    *((volatile unsigned char*)0x24) |= (1 << 5);
}

// toggle the pin
void toggle()
{
    *((volatile unsigned char*)0x23) |= (1 << 5);
}

int main(void)
{
    // PRTIM0 set to zero to enable Timer/Counter0
    // power_timer0_enable();
    PRR &= ~(1 << PRTIM0);

    // set the timer to CTC mode (clear timer on compare)
    TCCR0A |= 2;

    // set the compare register value
    OCR0A = 200;

    // enable the 1024 prescaler
    TCCR0B = 5;

    set_out();
    int counter = 0;
    while (1) {
        // if the flag has been set by the timer match to compare
        if (TIFR0 & 2) {
            TIFR0 = 2;
            counter++;
            if (counter < 50)
                continue;
            // toggle the output pin
	    toggle();

            // reset the flag
            counter = 0;
        }
    }

    return 0;
}
