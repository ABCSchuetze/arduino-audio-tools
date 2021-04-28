#include "Arduino.h"
#include "BluetoothA2DPSource.h"
#include "SoundTools.h"

using namespace sound_tools;  

/**
 * @brief We use a mcp6022 analog microphone as input and send the data to A2DP
 */ 

ADC adc;
BluetoothA2DPSource a2dp_source;

// callback used by A2DP to provide the sound data
int32_t get_sound_data(Channels* data, int32_t len) {
   // the ADC provides data in int16_t data which matches the definition of Channels
   return adc.read((arrayOf2int16_t*)data, len);   
}

// Arduino Setup
void setup(void) {
  Serial.begin(115200);

  // start i2s input with default configuration
  Serial.println("starting I2S-ADC...");
  adc.begin(adc.defaultConfig());

  // start the bluetooth
  Serial.println("starting A2DP...");
  a2dp_source.start("RadioPlayer", get_sound_data);  
}

// Arduino loop - repeated processing 
void loop() {
}