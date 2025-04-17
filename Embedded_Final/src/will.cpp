// #include <Arduino.h>
// #include <arduinoFFT.h>




// enum Level {
//     LEVEL_0,
//     LEVEL_1,
//     LEVEL_2,
//     LEVEL_3,
//     LEVEL_4,
//     LEVEL_5,
//     LEVEL_6,
//     LEVEL_7,
//     LEVEL_8,
//     LEVEL_9,
//     LEVEL_10
// };

// void FFT_test() {
//     int samples = 10; // Number of samples
//     int samplingFrequency = 1000; // Sampling frequency in Hz
//     double frequency = 50; // Frequency of the sine wave in Hz

//     double vReal[samples];
//     double vImag[samples];

//     // Fill vReal with a sine wave
//     for (int i = 0; i < samples; i++) {
//         vReal[i] = 100 * sin(2 * PI * frequency * i / samplingFrequency); // Amplitude of 100
//         vImag[i] = 0; // Imaginary part is 0
//     }

//     // Print the sine wave values
//     Serial.println("Sine Wave Values:");
//     for (int i = 0; i < samples; i++) {
//         Serial.print("Sample ");
//         Serial.print(i);
//         Serial.print(": ");
//         Serial.println(vReal[i]);
//     }
// }

// void setup(){
//     Serial.begin(9600);
//     delay(2000);
//     FFT_test();
// }

// void loop(){

// }