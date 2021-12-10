#include "ArxContainer.h"

// motors
const int enb_motor_1 = 9; // pwm pin motor 1
const int enb_motor_2 = 10; // pwm pin motor 2
const int in1 = 3; //first motor pin 1
const int in2 = 4;// first motor pin 2
const int in3 = 5;// second motor pin 1
const int in4 = 6; // second motor pin 2

const int motor_slow_value = 128;
const int motor_fast_value = 255;

// data setup
const int LABIRYNT_WIDTH = 16;
const int LABIRYNT_HEIGHT = 16;
const int BOX_LENGHT = 20; // cm

// vision sensor setup
const int trigPin = 1;
const int echoPin = 3;

struct Node {
  byte walls;
  byte x;
  byte y;
  short gCost;
  short hCost;
  short fCost;
  Node* parent;
};

inline bool operator > (const Node& n1, const Node& n2)
{
  return n1.fCost > n2.fCost;
}

inline bool operator == (const Node& n1, const Node& n2)
{
  if (n1.x == n2.x && n1.y == n2.y) {
    return true;
  }
  return false;
}

class AStar 
{
  public:
    Node start;
    Node destination;
    Node current;
    Node choice;
    Node data[LABIRYNT_WIDTH][LABIRYNT_HEIGHT];
    
  AStar (Node start, Node destination) 
  {
    this->start = start;
    this->destination = destination;
  };

  void FillData ()
  {
    for (int i = 0; i < LABIRYNT_WIDTH; i++) {
      for (int j = 0; j < LABIRYNT_HEIGHT; j++) {
        Node n {0, (byte)i, (byte)j, 0, 0, 0, NULL};
        this->data[i][j] = n;
      }
    }
  }
  
  int CalculateHCost ()
  {
    return this->destination.x - this->current.x + this->destination.y - this->current.y;
  };

  bool CheckRoute ()
  {
    int dir;
    if (this->choice.x < this->current.x) dir = 0; // left
    if (this->choice.x > this->current.x) dir = 1; // right
    if (this->choice.y > this->current.y) dir = 2; // top
    if (this->choice.y < this->current.y) dir = 3; // bottom
    return (bool)get_bit(this->current.walls, dir);
  }

  arx::vector<Node> GetPath ()
  {
     arx::vector<Node> path = arx::vector<Node>();
     Node active_node = this->current;
     while (active_node.parent != NULL) 
     {
        path.push_back(active_node);
        active_node = *active_node.parent;
     }
     return path;
  }

  arx::vector<Node> FindPath () 
  {
    arx::vector<Node> to_process = arx::vector<Node>();
    arx::vector<Node> closed = arx::vector<Node>();

    to_process.push_back(this->current);

    while (to_process.size() > 0)
    {
      if (this->current == this->destination) {
        return GetPath();
      }
      
    }
    return to_process;
  }
  
};

// detecting distance 
bool check_wall(int return_distance)
{
  digitalWrite(trigPin, LOW);

  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  double distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if ((int)distance < return_distance) return true;
  return false;
}

// bit operations
byte set_bit (byte data, int n) {
  unsigned int bit_index = n % 8;
  byte bit_mask = (1 << bit_index);

  return data |= bit_mask;
}

byte clear_bit (byte data, int n) {
  unsigned int bit_index = n % 8;
  byte bit_mask = (1 << bit_index);

  return data &= ~bit_mask;
}

byte get_bit (byte data, int n) {
  unsigned int bit_index = n % 8;
  byte bit_mask = (1 << bit_index);

  return (data & bit_mask) != 0;
}

// motor controls 
void set_motor_power (int motor, int power){
  if (motor == 1) {
    analogWrite(enb_motor_1, power);
  } else if (motor == 2) {
    analogWrite(enb_motor_2, power);
  }
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

void forward (int power) {
  set_direction(1, 1);
  set_direction(2, 1);
  set_motor_power(1, power);
  set_motor_power(2, power);
}

void backward (int power) {
  set_direction(1, -1);
  set_direction(2, -1);
  set_motor_power(1, power);
  set_motor_power(2, power);
}

void turn_left (int power, int duration)
{
  set_direction(1, -1);
  set_direction(2, 1);
  set_motor_power(1, power);
  set_motor_power(2, power);
}

void turn_right (int power, int duration)
{
  set_direction(1, 1);
  set_direction(2, -1);
  set_motor_power(1, power);
  set_motor_power(2, power);
}

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enb_motor_1, OUTPUT);
  pinMode(enb_motor_2, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  forward(motor_fast_value);
  delay(2000);
  forward(motor_slow_value);
  delay(2000);
  backward(motor_fast_value);
  delay(2000);
  backward(motor_slow_value);
  delay(2000);
}
