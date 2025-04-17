#include <Arduino.h>
#include <arduinoFFT.h>
#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02
#define SCL_PLOT 0x03
#define samples 10 
#define samplingFrequency 1000 
#define frequency 50 

// Function prototype
void PrintVector(double *vData, uint16_t bufferSize, uint8_t scaleType);

enum Level {
    LEVEL_0,
    LEVEL_1,
    LEVEL_2,
    LEVEL_3,
    LEVEL_4,
    LEVEL_5,
    LEVEL_6,
    LEVEL_7,
    LEVEL_8,
    LEVEL_9,
    LEVEL_10
};

ArduinoFFT<double> FFT_test() {
    

    double vReal[samples];
    double vImag[samples];

    for (int i = 0; i < samples; i++) {
        vReal[i] = 100 * sin(2 * PI * frequency * i / samplingFrequency); 
        vImag[i] = 0; 
    }

    Serial.println("Sine Wave Values:");
    for (int i = 0; i < samples; i++) {
        Serial.print("Sample ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(vReal[i]);
    }
    ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, samples, samplingFrequency);
    //FFT occurs

    Serial.println("Data:");
    PrintVector(vReal, samples, SCL_TIME);
    FFT.windowing(FFTWindow::Hamming, FFTDirection::Forward);	/* Weigh data */
    Serial.println("Weighed data:");
    PrintVector(vReal, samples, SCL_TIME);
    FFT.compute(FFTDirection::Forward); /* Compute FFT */
    Serial.println("Computed Real values:");
    PrintVector(vReal, samples, SCL_INDEX);
    Serial.println("Computed Imaginary values:");
    PrintVector(vImag, samples, SCL_INDEX);
    FFT.complexToMagnitude(); /* Compute magnitudes */
    Serial.println("Computed magnitudes:");
    PrintVector(vReal, (samples >> 1), SCL_FREQUENCY);
}

void PrintVector(double *vData, uint16_t bufferSize, uint8_t scaleType)
{
  for (uint16_t i = 0; i < bufferSize; i++)
  {
    double abscissa;
    /* Print abscissa value */
    switch (scaleType)
    {
      case SCL_INDEX:
        abscissa = (i * 1.0);
        break;
      case SCL_TIME:
        abscissa = ((i * 1.0) / samplingFrequency);
        break;
      case SCL_FREQUENCY:
        abscissa = ((i * 1.0 * samplingFrequency) / samples);
        break;
    }
    Serial.print(abscissa, 6);
    if (scaleType == SCL_FREQUENCY)
      Serial.print("Hz");
    Serial.print(" ");
    Serial.println(vData[i], 4);
  }
  Serial.println();
}

void setup() {
    Serial.begin(9600);
    delay(2000);
    FFT_test();
}

void loop() {
    
}