
#define trigPin 2
#define echoPin 3

long duration;
int distance;
int return_distance = 10;
bool is_wall = false;


bool check_wall()
{
  is_wall = false;
  digitalWrite(trigPin, LOW);

  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  if (distance < return_distance)
  {
    is_wall = true;
  }  
  return(is_wall);
}
void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
} 

void loop ()
{
  Serial.println("a");
}
