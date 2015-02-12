#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

int PIXEL_NUM = 13;
long tMilli = 0;
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  Serial.begin(115200);
  tMilli = millis();
}

float potVal = 200;
int a[8] = {0, 0, 0, 0, 0, 0, 0, 0};
void loop() {
  for(int i=0; i<13; i++){
    strip.setPixelColor(i, 0, 0, 0);
  }
  
  for (int i=0; i<8; i++){
    a[i] = analogRead(i);
  }
  int pot = analogRead(8);
  /*
  a[0] = map(a[0], 80, 530, 0, 10);
  a[2] = map(a[2], 80, 530, 0, 10);
  a[4] = map(a[4], 80, 530, 0, 10);
  a[6] = map(a[6], 80, 530, 0, 10);
  a[1] = map(a[1], 450, 660, 2, 6);
  a[3] = map(a[3], 450, 660, 2, 6);
  a[5] = map(a[5], 450, 660, 2, 6);
  a[7] = map(a[7], 450, 660, 2, 6);
  int potDisplay = map(pot, 0, 1024, 0, 10);
  
  long cMilli = millis();
  if(cMilli - tMilli > 800){
    Serial.print("4 ");
    for (int i=0; i<8; i++){
      Serial.print(a[i]);
      Serial.print(" ");
    }
    Serial.print(potDisplay);
    Serial.println();
    tMilli = cMilli;
  }
  */
  Serial.print("4 ");
  for (int i=0; i<8; i++){
    Serial.print(a[i]);
    Serial.print(" ");
  }
  Serial.print(pot);
  Serial.println();
  potVal = (float)(pot)*0.2 + potVal*0.8;
  int onLightNum = (potVal)*PIXEL_NUM/1024;
  
  for(int i=0; i<onLightNum; i++){
    strip.setPixelColor(i, 0, 0, i*150/13);
  }
  strip.show();
}
