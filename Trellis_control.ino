#include "Adafruit_NeoTrellisM4.h"

// The NeoTrellisM4 object is a keypad and neopixel strip subclass
// that does things like auto-update the NeoPixels and stuff!
Adafruit_NeoTrellisM4 trellis = Adafruit_NeoTrellisM4();

int color;
int brightness;

void setup(){
  Serial.begin(115200);
  while (!Serial);
  
  trellis.begin();
  trellis.setBrightness(80);

  Serial.println("CommandReady");
}

void parseSerialCommands() {
  if(Serial.available() > 0) {
    brightness = Serial.parseInt();
    trellis.setBrightness(brightness);
    for(int i = 0; i < trellis.num_keys(); i++) {
      color = Serial.parseInt();
      trellis.setPixelColor(i, color);
    }
  } 
}
  
void loop() {
  // put your main code here, to run repeatedly:
  trellis.tick();
  parseSerialCommands();
  
  while (trellis.available()){
    keypadEvent e = trellis.read();
    
    if (e.bit.EVENT == KEY_JUST_PRESSED) {
      int key = e.bit.KEY;  // shorthand for what was pressed
      Serial.println(key);
    }
  }
  
  delay(10);
}
