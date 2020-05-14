#include <Wire.h>
#include <FastLED.h>
#define NUM_LEDS 60
#define LED_PIN 2

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=265;
int maxVal=402;

double x;
double y;
double z;
 
CRGB led[NUM_LEDS];

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  
  FastLED.addLeds<NEOPIXEL, LED_PIN>(led, NUM_LEDS);
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

void driveLeds(float angle){

  int active_led = angle/(360/NUM_LEDS);
  Serial.println(active_led);
  
  for(int i=0; i<NUM_LEDS; i++){
    led[i] = i==active_led ? CRGB(255,0,0) : CRGB(0,0,0);
  }
  FastLED.show();
  
}

void loop() {

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  
  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  
  int xAng = map(AcX,minVal, maxVal,-90, 90);
  int yAng = map(AcY,minVal, maxVal,-90, 90);
  int zAng = map(AcZ,minVal, maxVal,-90, 90);

  x= RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

  Serial.print("AngleX= ");
  Serial.println(x);
  
  Serial.print("AngleY= ");
  Serial.println(y);
  
  Serial.print("AngleZ= ");
  Serial.println(z);
  Serial.println("-----------------------------------------");

  driveLeds(x);
  
//  int sensorValue = analogRead(A0); 
//  float voltage = sensorValue*(5.0/1023.0);
//  Serial.println(voltage);

  //setRed(voltage);
}
