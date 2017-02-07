#include "pitches.h"

#define buzzer_pin 3

bool do_beep_beep = false;
bool do_warning = false;

void buzzer_setup(){
  pinMode(buzzer_pin, OUTPUT);
}

void buzzer_loop(){
  if (get_start()) {do_beep_beep = true;}
  if (do_beep_beep) beep_beep();
  if (get_bat_charge() < 750) do_warning = true;
  if (do_warning) warning();
}


void beep_beep(){
  static long next_beep = 0;
  static int beep_count = 0;

  if (beep_count == 2){
    beep_count = 0;
    do_beep_beep = false;
    return;
  }

  if (millis() > next_beep){
    tone(buzzer_pin, NOTE_A6, 200);
    next_beep = millis() + 250;
    beep_count++;
  }
}

void warning(){
  static long next_beep = 0;
  static int beep_count = 0;

  if (beep_count == 2){
    beep_count = 0;
    do_warning = false;
    return;
  }

  if (millis() > next_beep){
    tone(buzzer_pin, NOTE_E5, 200);
    next_beep = millis() + 1000;
    beep_count++;
  }
}

void set_do_beep_beep(){
  do_beep_beep = true;
}

void set_do_warning(){
  do_warning = true;
}
