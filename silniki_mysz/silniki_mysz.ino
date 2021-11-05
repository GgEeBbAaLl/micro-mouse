// (c) Michael Schoeffler 2016, http://www.mschoeffler.de

const int enb = 9; // pwn pin
const int in1 = 6; //first motor pin 1
const int in2 = 7;// first motor pin 2
const int in3 = 3;// second motor pin 1
const int in4 = 2; // second motor pin 2

const int motor_slow_value = 128;
const int motor_fast_value = 255;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enb, OUTPUT);
}

void stop_motor (){
  analogWrite(enb, 0);
}

void slow() {
  analogWrite(enb, motor_slow_value);
}

void fast() {
  analogWrite(enb, motor_fast_value);
}

void set_direction(int motor, int n) { // motor = 1 or 2 (representing motor number)
  if (motor == 1) {
    if (n == 1){
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
    } else if (n == -1) {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
    }
  } else if (motor == 2) {
    if (n == 1) {
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
    } else if (n == -1) {
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
    }
  }
}

void loop() {
  set_direction(1, 1);
  set_direction(2, 1);
  // digitalWrite(in3, LOW);
  // digitalWrite(in4, HIGH);
  slow();
  delay(5000);
  fast();
  delay(5000);
  // change of direction
  set_direction(1, -1);
  set_direction(2, -1);
  slow();
  delay(5000);
  fast();
  delay(5000);
}
