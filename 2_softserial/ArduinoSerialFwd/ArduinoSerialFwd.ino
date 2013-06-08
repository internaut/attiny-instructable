/* Name: ArduinoSerialFwd
 * This is just an example for AVR-C with ATtiny microcontrollers. The code
 * implements an example of how to use softuart. This Arduino code is for
 * forwarding the serial data from the ATtiny to a serial monitor program
 * on your computer.
 *
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

#include <SoftwareSerial.h>

#define HARD_SERIAL_BAUD_RATE  115200
#define SOFT_SERIAL_BAUD_RATE  2400
#define SOFT_SERIAL_RX  10
#define SOFT_SERIAL_TX  11

SoftwareSerial softSerial(SOFT_SERIAL_RX, SOFT_SERIAL_TX); // RX, TX

int inByte;

void setup() {
  Serial.begin(HARD_SERIAL_BAUD_RATE);
  softSerial.begin(SOFT_SERIAL_BAUD_RATE);
}

void loop() {
  if (softSerial.available()) {  // forward soft serial RX to hard serial TX
    Serial.write(softSerial.read());
  }
  
  if (Serial.available()) {      // forward hard serial RX to soft serial TX
    softSerial.write(Serial.read());
  }
}
