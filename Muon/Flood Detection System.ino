// Include Particle Device OS APIs
#include "Particle.h"

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);


// Declare variables
  int powerA = D2;
  int signalA = A5;
   
  int valA = 0;
  bool alerted = 0;
    
// setup() runs once, when the device is first turned on
void setup(){
    // Sensor pinMode
    pinMode(powerA, OUTPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop(){
    
    delay(100);
    digitalWrite(powerA, HIGH);
    delay(1000);
    valA = analogRead(signalA);
    digitalWrite(powerA, LOW);
    
    // -- TESTING -- If you encounter unusual readings or a lack of alert, ensure pinout is correct.
    // -- TESTING -- Uncomment the lines below and comment out the if statement below
    //Particle.publish("Sensor A - Water Level: ", String(valA));
    //delay(2000);
    
    if (valA >= 5){                                                                 // When the contact switch closes, it makes relevant val high 
        Particle.publish("FLOOD ALERT - Sensor A - Water Level:", String(valA));    // Publish the Water Sensor alert
        alerted = 1;
    }
                                                                                    // If adding more sensors, place them here before the alerted check
    if (alerted == 1){
        delay(600000);                                                              // Wait for 10 minutes to give a chance to respond
    }

}
