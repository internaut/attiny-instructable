/* Name: main.c
 * This is just an example for AVR-C with ATtiny microcontrollers. The code
 * implements an example of how to use softuart.
 * It is part of the following instructable: 
 *
 * Author: Markus Konrad
 * Copyright 2013. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification,are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * Neither the name of the mkonrad.net nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "softuart.h"

// Define your softuart pin in softuart.h!

// Define some macros

#define PRINT_NL softuart_putchar( '\n' )

// Define function to write an integer to serial out
#define PRINT_INT_BUFSIZE	16
void printInt(int32_t i) {
	char buf[PRINT_INT_BUFSIZE];
	int8_t sign = 1;
	int8_t len = 0;

	if (i < 0) { // look for the sign
		sign = -1;
		i = -i;
	}

	// fill buffer with digits (in reverse order)
	do {
		buf[len++] = 48 + i % 10;	// ASCII digits start at 48
	} while ((i /= 10) > 0 && len < PRINT_INT_BUFSIZE);

	if (sign < 0) {	// don't forget to add the sign
		buf[len] = '-';
	} else {
		len--;
	}

	// reverse output of the buffer
	do {
		softuart_putchar(buf[len--]);
	} while (len >= 0);
}


// program entry point
int main(void) {
    // DDRB for the UART TX will be set in the softuart_init() function!
    
    // we neet to init softuart
	softuart_init();
	softuart_turn_rx_off();    // we don't receive serial data

	sei(); // this enables interupts, which are needed for softuart
        
    // main loop
    int8_t i = -128;
    int8_t d = 1;
    for(;;){
        softuart_putchar('i');
        softuart_putchar('=');
        printInt(i);
        PRINT_NL;
        
        if (i == 127) d = -1;   // count down
        if (i == -128) d = 1;   // count up
        
        i += d;
        
        // make a small delay
        _delay_ms(20);
    }
    
    return 0;   /* never reached */
}
