#include <Arduino.h>
#include <Adafruit_CircuitPlayground.h>
#include <arduinoFFT.h>
#include <math.h>

// Indicators
#define RED 0xFF0000 // Dyskenesia
#define GREEN 0x00FF00 // Normal
#define YELLOW 0xFFFF00 // Parkinsons
#define ORANGE 0xFFA500 // Between Dyskenesia and Parkinsons
#define PARKINSON_LOW 3.0
#define PARKINSON_HIGH 5.0
#define DYSKINESIA_LOW 5.0
// #define DYSKINESIA_HIGH 7.0

// FFT
#define SAMPLES 128
#define SAMPLING_FREQUENCY 45 

double vReal[SAMPLES];
double vImag[SAMPLES];

ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLES, SAMPLING_FREQUENCY);

// State machine
enum State {
  RECORDING,
  ANALYZING,
  WAITING
};

// Variables
double movementThreshold = 0.3; // Threshold for movement detection

State currentState = RECORDING;
unsigned long lastSampleTime = 0;
int sampleIndex = 0;
unsigned long waitStartTime = 0;
const long waitDuration = 2000; // Wait 2 seconds between analyses

float peakFrequency = 0;
float peakMagnitude = 0;
int intensity = 0; // 0-5 intensity scale

void setup() {
  CircuitPlayground.begin(); // Initialize circuit playground

  Serial.begin(115200);
  while(!Serial);
  Serial.println("Ready");
}

void analyzeData() {
  Serial.println("Performing FFT analysis...");
  
  // Prepare the FFT
  FFT.windowing(FFTWindow::Hamming, FFTDirection::Forward);
  FFT.dcRemoval();
  FFT.compute(FFTDirection::Forward);
  FFT.complexToMagnitude();
  
  peakFrequency = 0;
  peakMagnitude = 0;
  
  // Print FFT results for debugging
  Serial.println("Frequency\tMagnitude");
  
  for (int i = 0; i < SAMPLES/2; i++) {
    float frequency = (i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES;
    
    // removes the DC component and low frequencies
    if (frequency >= 2.0 && frequency <= 8.0) {
      Serial.print(frequency);
      Serial.print("\t\t");
      Serial.println(vReal[i]);
      
      if (vReal[i] > peakMagnitude) {
        peakMagnitude = vReal[i];
        peakFrequency = frequency;
      }
    }
  }
  
  // Determine condition based on peak frequency
  if (peakFrequency >= PARKINSON_LOW && peakFrequency < PARKINSON_HIGH) {
    Serial.println("*** PARKINSON DETECTED ***");
    // need to reset Axis X,Y and Z
  } else if (peakFrequency >= DYSKINESIA_LOW) {
    Serial.println("*** DYSKINESIA DETECTED ***");
  } else {
    Serial.println("*** NO MOVEMENT DISORDER DETECTED ***");
  }
  
  // Summary output
  Serial.print("Peak Frequency: ");
  Serial.print(peakFrequency);
  Serial.print(" Hz, Magnitude: ");
  Serial.print(peakMagnitude);
  Serial.println("-----------------------------");
}

void loop() {
  unsigned long currentMillis = millis();
  
  switch (currentState) {
    case RECORDING:
      // Time to collect the next sample?
      if (currentMillis - lastSampleTime >= (1000 / SAMPLING_FREQUENCY)) {
        lastSampleTime = currentMillis;
        
        // Read accelerometer data
        float x = CircuitPlayground.motionX();
        float y = CircuitPlayground.motionY();
        float z = CircuitPlayground.motionZ();
        
        // Calculate the magnitude of the acceleration vector
        float magnitude = sqrt((x * x) + (y * y) + (z * z));
        
        // Store the sample
        vReal[sampleIndex] = magnitude;
        vImag[sampleIndex] = 0.0; // Imaginary part must be zeroed
        
        // Debug output (optional)
        if (sampleIndex % 10 == 0) { // every 10 samples
          Serial.print("Sample ");
          Serial.print(sampleIndex);
          Serial.print(": ");
          Serial.println(magnitude);
        }
        
        sampleIndex++;
        
        // Samples are full, switch to analyzing
        if (sampleIndex >= SAMPLES) {
          Serial.println("Recording complete. Starting analysis...");
          currentState = ANALYZING;
        }
      }
      break;
      
    case ANALYZING:
      analyzeData();
      waitStartTime = currentMillis;
      currentState = WAITING;
      break;
      
    case WAITING:
      // Return to recording after wait duration
      if (currentMillis - waitStartTime >= waitDuration) {
        // Reset for next recording
        sampleIndex = 0;
        Serial.println("Starting new recording cycle...");
        currentState = RECORDING;
      }
      break;
  }
}
