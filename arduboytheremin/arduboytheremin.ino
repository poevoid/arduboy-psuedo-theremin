#include <Arduboy2.h>
#include "noiseInput.h"

Arduboy2 arduboy;
BeepPin2 beep;

float frequency = 523.251;

int x;
int y[WIDTH];

void clearY(){
  for (int i=0; i<WIDTH; i++){
    y[i] = -1;
  }
}

void drawY(){
  arduboy.drawPixel(0, y[0], WHITE);
  for(int i=1; i<WIDTH; i++){
    if (y[i] != -1) {
      //arduboy.drawPixel(i, y[i]);
      arduboy.drawLine(i-1, y[i-1], i, y[i]);
    }else {
      break;
    }
  }
}
void setup() {
  // put your setup code here, to run once:
  arduboy.begin();
  beep.begin();
  ENIDpadSetup();
  Serial.begin(9600);
  x = 0;
  clearY();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!arduboy.nextFrame())return;
  arduboy.clear();
  arduboy.setCursor(0,0);
  y[x] = map(ENIPinRead(), 0, 1023, HEIGHT-1, 0);
  drawY();
  x++;
  if(x >=WIDTH){
    x = 0;
    clearY();
  }
  frequency = ENIPinRead();
  beep.tone(beep.freq(frequency));
  Serial.println(ENIPinRead());
  arduboy.display();
}
