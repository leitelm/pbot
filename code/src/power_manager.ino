#include "pitches.h"

#define cell_1 A4

int bat_charge = 0;

void power_setup(){
  pinMode(cell_1, INPUT);
}

void power_loop(){
  static long next_publish = 0;
  if  (millis() > next_publish){
    bat_charge = 2*map(analogRead(cell_1),0,1023,0,500);
    Serial.print("Bat Charge 1 ");
    Serial.print(bat_charge);
    Serial.println("v");
    next_publish = millis() + 1000;
  }
}

int get_bat_charge(){
  if (millis() > 100) return bat_charge;
  return 850;
}
