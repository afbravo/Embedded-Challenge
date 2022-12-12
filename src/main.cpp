#include <Arduino.h>


/*
the device will be doing the following:

1. read pulse 
   if the pulse is below treshold BPM
    -> we measure the pressure on chest
    if pressure < treshold
     -> not breathing

2. read pressure
    if pressure < treshold
      check pulse
      if pulse < treshold
        -> not breathing

also need
  - a timer to keep track of time since last detection

*/

#define pulse_pin 0
#define pressure_pin 1
/*
pressure sensor range 100 - 5000 grams
*/

#define pressure_treshold 1 //need to change !!

#define pulse_treshold 1 //Need to change !!

#define time_treshold 10000 // 10 seconds / 10000 milliseconds

long int bpm = 0;
long int pressure = 0; // in grams
bool alert = false;

void getBPM(long int *bpm){
  // read pulse
  // calculate bpm
  // change bpm
}

void getPressure(long int *pressure){
  int val = analogRead(pressure_pin);
  *pressure = map(val, 0, 1023, 100, 5000); //assuming the sensor is linear (need to check)
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  getBPM(&bpm);

  if(bpm < pulse_treshold){
    // check pressure
    getPressure(&pressure);
    if(pressure < pressure_treshold){
      alert = true;
      Serial.println("alert");
    }
    else{
      alert = false;
    }
  }
  else{
    alert = false;
  }

  if(alert && timer < time_treshold){
    // not breathing
    Serial.println("Not Breathing");
  }

  Serial.println(bpm);
  Serial.println(pressure);
  Serial.println("Breathing");
  delay(10);
}