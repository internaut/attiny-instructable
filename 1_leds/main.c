/* Name: main.c
 * This is just an example for AVR-C with ATtiny microcontrollers. The code
 * implements digital switching of two pins, letting two connected LEDs blink.
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
#include <util/delay.h>

// Define pins

#define PIN_LED1    PB0
#define PIN_LED2    PB1

// Define the delay time in ms

#define DELAY_MS    500

// Define helper macros

// write digital "high" to pin <pn> on port <prt>
#define DIGIWRITE_H(prt, pn) prt |= (1<<pn)

// write digital "low" to pin <pn> on port <prt>
#define DIGIWRITE_L(prt, pn) prt &= ~(1<<pn)

// Define long delay function

void long_delay_ms(uint16_t ms) {
    for(ms /= 10; ms>0; ms--) _delay_ms(10);
}

// program entry point
int main(void) {
    // DDRB is the "data direction register" for port B
    // the ATtinyX5 only has port B with usable pins
    // we set both LED pins to "output"
    DDRB |= (1 << PIN_LED1) | (1 << PIN_LED2);
    
    // initially set the pins to "low"
    DIGIWRITE_L(PORTB, PIN_LED1);
    DIGIWRITE_L(PORTB, PIN_LED2);
    
    // main loop
    uint8_t toggle = 0;
    for(;;){
        // alternate between the LEDs to let them blink
        DIGIWRITE_L(PORTB, (toggle == 0 ? PIN_LED1 : PIN_LED2));
        DIGIWRITE_H(PORTB, (toggle == 0 ? PIN_LED2 : PIN_LED1));
        
        // alternave the toggle variable
        toggle = !toggle;
        
        // make a long delay
        long_delay_ms(DELAY_MS);
    }
    
    return 0;   /* never reached */
}
