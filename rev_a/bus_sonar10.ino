// Copyright (c) 2014 by Wayne C. Gramlich.  All rights reserved.
//
// This code drives the bus_sonar10 module.


// Sonars are organized in trigger/echo pairs.  There are
// 10 sonars (SONARS_SIZE == 10).  In order to 1) conserve
// pins and 2) ensure that each echo return is routed to
// a pin connected to one of the 6 counter/timer pins,
// some sonars share an echo pin.  Thus, sonar 0/1, 3/4,
// 5/6, and 8/9 can not both be triggered at the same time.


#define SONARS_SIZE 10
struct Sonar_Struct {
  uint8_t trigger;
  uint8_t echo;
} sonars[SONARS_SIZE] = {
  (uint8_t)A1, (uint8_t)9,  // sonars[0]
  (uint8_t)13, (uint8_t)9,  // sonars[1]
  (uint8_t)A0, (uint8_t)6,  // sonars[2]
  (uint8_t)12, (uint8_t)5,  // sonars[3]
  (uint8_t)8,  (uint8_t)5,  // sonars[4]
  (uint8_t)A3, (uint8_t)11, // sonars[5]
  (uint8_t)A2, (uint8_t)11, // sonars[6]
  (uint8_t)7,  (uint8_t)10, // sonars[7]
  (uint8_t)4,  (uint8_t)3,  // sonars[8]
  (uint8_t)2,  (uint8_t)3,  // sonars[9]
};

// the setup routine runs once when you press reset:
void setup() {
  // Initialize the Serial Port:
  Serial.begin(115200);
  
  // Initialize the trigger/echo pin pairs:
  for (uint8_t index = 0; index < SONARS_SIZE; index++) {
    pinMode(sonars[index].trigger, OUTPUT);
    pinMode(sonars[index].echo, INPUT);
  }
}

// the loop routine runs over and over again forever:
void loop() {
  // Iterate across all of the sonars:
  //FIXME: For now we only look at sonar 0!!!
  for (uint8_t index = 0; index < 1; index++) {
    // Trigger the sonar:
    uint8_t trigger = sonars[index].trigger;
    digitalWrite(trigger, LOW);
    delayMicroseconds(10);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);
    delayMicroseconds(5);
    
    // Time the echo pulse:
    uint8_t echo = sonars[index].echo;
    uint32_t duration = pulseIn(echo, HIGH);

    // Print out the result:
    uint32_t inches = duration / 74 / 2;
    uint32_t centimeters = duration / 29 / 2;
    Serial.print("Sonar[");
    Serial.print(index);
    Serial.print("]: ");
    Serial.print(centimeters);
    Serial.print("cm ");
    Serial.print(inches);
    Serial.print("in ");
    Serial.print(duration);
    Serial.print("raw\r\n");
  }
}
