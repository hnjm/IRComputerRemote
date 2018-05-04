/*
   IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
   An IR detector/demodulator must be connected to the input RECV_PIN.
   Version 0.1 July, 2009
   Copyright 2009 Ken Shirriff
   http://arcfn.com
*/

#include <boarddefs.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <IRremoteInt.h>
#include <IRremote.h>

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  pinMode(A5, OUTPUT);

  Serial.begin(115200);
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Setupd finished");
  for (int i = 0; i < 10; i++) {
    analogWrite(A5, 255);
    delay(50);
    analogWrite(A5, 0);
    delay(50);
  }

}

void loop() {
  // Data send by computer on serial port
  if (Serial.available() > 0) {
    // read the incoming byte:
    int incomingByte = Serial.read();

    if (incomingByte == 48) {
      analogWrite(A5, 255); // Led ON
      delay(100);
      Serial.println("Hello!");
    } else {
      analogWrite(A5, 0); // Led OFF
    }

    // say what you got:
    // Serial.print("I received: ");
    // Serial.println(incomingByte, HEX);
  }

  // IR receiver
  /*if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
    }*/

}
