#include <Arduino.h>
#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>


#define SAMPLE_RATE 50  //Hz
#define DURATION 3      // sec
#define NUM_SAMPLES (SAMPLE_RATE * DURATION)


float ax[NUM_SAMPLES];
float ay[NUM_SAMPLES];
float az[NUM_SAMPLES];


void setup() {
  CircuitPlayground.begin();
  delay(1000);


  CircuitPlayground.setPixelColor(0, 255, 0, 0);
  delay(500);


  collectAccelerometerData();


  CircuitPlayground.setPixelColor(0, 0, 255, 0);
}


void loop() {
 
}


void collectData() {
  unsigned long interval = 1000 / SAMPLE_RATE;


  for (int i = 0; i < NUM_SAMPLES; i++) {
    sensors_event_t event;
    CircuitPlayground.motionSensor.getEvent(&event);


    ax[i] = event.acceleration.x;
    ay[i] = event.acceleration.y;
    az[i] = event.acceleration.z;


    delay(interval);
  }
}
