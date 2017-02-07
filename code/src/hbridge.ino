#define ENA 5
#define ENB 6
#define IN1 A0
#define IN2 A1
#define IN3 A2
#define IN4 A3

void hbridge_setup(){
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

bool run_once = true;

void hbridge_loop(){
  if (run_once) {
    if (millis() > 1000) run_once = false;
    return;
  }

  basic_controller();
}

const int min_forward_speed = 100;
const int min_turn_speed = 150;
const int high_threshold = 130;
const int low_threshold = 120;

int get_speed(int joy_val, bool turning=false){
  if (turning){
    // Esquerda
    if (joy_val < low_threshold){
      return map(joy_val, low_threshold, 0, min_turn_speed, 255);
    }
    // Direita
    if (joy_val > high_threshold){
      return map(joy_val, high_threshold, 255, min_turn_speed, 255);
    }
  }
  // Frente
  if (joy_val < low_threshold){
    return map(joy_val, low_threshold, 0, min_forward_speed, 255);
  }
  // Tras
  if (joy_val > high_threshold){
    return map(joy_val, high_threshold, 255, min_forward_speed, 255);
  }
}

void basic_controller(){
  int lx_val = get_lx();
  int ly_val = get_ly();
  // DIREITA
  if (lx_val > high_threshold){
    analogWrite(ENA, get_speed(lx_val, true));
    analogWrite(ENB, get_speed(lx_val, true));
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    return;
  }
  if (lx_val < low_threshold){
    analogWrite(ENA, get_speed(lx_val, true));
    analogWrite(ENB, get_speed(lx_val, true));
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    return;
  }
  // TRAS
  if (ly_val > high_threshold){
    analogWrite(ENA, get_speed(ly_val));
    analogWrite(ENB, get_speed(ly_val));
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    return;
  }
  // FRENTE
  if (ly_val < low_threshold){
    analogWrite(ENA, get_speed(ly_val));
    analogWrite(ENB, get_speed(ly_val));
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    return;
  }
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
