/*
   IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
   An IR detector/demodulator must be connected to the input RECV_PIN.
   Version 0.1 July, 2009
   Copyright 2009 Ken Shirriff
   http://arcfn.com
*/

#include "boarddefs.h"
//#include <ir_Lego_PF_BitStreamEncoder.h>
#include "IRremoteInt.h"
#include "IRremote.h"

int SHORT_LED_BLINK_MS = 50;
int LONG_LED_BLINK_MS = 100;

int RECV_PIN = 11;
int LED = 19;

IRrecv irrecv(RECV_PIN);

decode_results results;

void ledBlink(const int _periodMs)
{
  for (int i = 0; i < 10; i++) {
    analogWrite(LED, 255);
    delay(_periodMs);
    analogWrite(LED, 0);
    delay(_periodMs);
  }
}

void setup()
{
  pinMode(LED, OUTPUT);

  Serial.begin(115200);
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Setupd finished");

  ledBlink(LONG_LED_BLINK_MS);
}

void loop() {
  
  // Command received from computer using serial interface
  if (Serial.available() > 0) {
    int serialDataReceived = Serial.read();

    if (serialDataReceived == 48) {
      ledBlink(SHORT_LED_BLINK_MS);
      Serial.println("Command received from computer");
      // TODO: Send a command to IR light bulb using IR led
    }
  }

  // Command received from IR remote control
  // TODO: Send a command to the computer according to IR code received from remote
  /*if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
    }*/

}
