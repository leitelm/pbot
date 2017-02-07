#include <Arduino.h>
#include <PS2X_lib.h>  //for v1.6

void setup(){
  ps2_setup();
  sonar_setup();
  hbridge_setup();
  power_setup();
}

void loop(){
  ps2_loop();
  sonar_loop();
  buzzer_loop();
  hbridge_loop();
  power_loop();
}
