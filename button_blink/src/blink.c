#define F_CPU 16000000UL
#include <util/delay.h>

// output: pb5
// input:  pb4

int main(void)
{
    // set pb5 as input
    *((volatile unsigned char*)0x24) |= (1 << 5);

    // set pb4 as output
    *((volatile unsigned char*)0x24) &= ~(1 << 4);
    // turn the pb4 pullup resistor on
    *(volatile unsigned char*)0x25 |= (1 << 4);


    while (1) {
	// get pinb4 value
	int button = (*(volatile unsigned char*)0x23)&(1<<4);
	if(!button)
	    *(volatile unsigned char*)0x25 |= (1 << 5);
	else
	    *(volatile unsigned char*)0x25 &= ~(1 << 5);
        _delay_ms(50);
    }
    return 0;
}
