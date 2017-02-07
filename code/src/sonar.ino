// Ultrasonic - Library for HR-SC04 Ultrasonic Ranging Module.
// Rev.4 (06/2012)
// J.Rodrigo ( www.jrodrigo.net )
// more info at www.ardublog.com

#include <Ultrasonic.h>

Ultrasonic ultraleft(4,7);   // (Trig PIN,Echo PIN)
Ultrasonic ultraright(8,9);  // (Trig PIN,Echo PIN)

#define pressao1 A4
#define pressao2 2

int sonar1cm, sonar2cm;
bool pressao1_state = false;
bool pressao2_state = false;

int get_sonar1(){
  return sonar1cm;
}
int get_sonar2(){
  return sonar2cm;
}

bool get_pressao1(){
  return pressao1_state;
}

bool get_pressao2(){
  return pressao2_state;
}

void sonar_setup() {
  pinMode(pressao1, INPUT_PULLUP);
  pinMode(pressao2, INPUT_PULLUP);
}

void sonar_loop()
{
  sonar1cm = ultraleft.Ranging(CM);
  sonar2cm = ultraright.Ranging(CM);
  pressao1_state = !digitalRead(pressao1);
  pressao2_state = !digitalRead(pressao2);
}
