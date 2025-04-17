#include <Arduino.h>
#include <arduinoFFT.h>




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

void FFT_test(){
int samples = 10;//this will be the number of samples
int sampling_freq = 1000;


double vReal[samples];
double vImag[samples];
ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, samples, samplingFrequency);


}





void setup(){
    Serial.begin(9600);
}

void loop(){

}