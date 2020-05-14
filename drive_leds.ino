#include <FastLED.h>
#define NUM_LEDS 60
#define LED_PIN 2

CRGB led[NUM_LEDS];
void setup() {
  
  FastLED.addLeds<NEOPIXEL, LED_PIN>(led, NUM_LEDS);
//  for(int i=0; i<NUM_LEDS; i++){
//    led[i] = CRGB(255,0,0);
//  }
//  FastLED.show();

  Serial.begin(9600);
}

void setRed(float voltage){
 
  for(int i=0; i<NUM_LEDS; i++){
    int led_index = NUM_LEDS/5*voltage; 
    Serial.println(led_index);
    led[i] = i==led_index ? CRGB(255,0,0) : CRGB(0,0,0);
  }
  FastLED.show();
  
}

void loop() {

  int sensorValue = analogRead(A0); 

  float voltage = sensorValue*(5.0/1023.0);

  Serial.println(voltage);

  setRed(voltage);
}
