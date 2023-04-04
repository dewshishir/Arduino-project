

/*
  SMART DUSTBIN ARDUINO CODE

  Lid of the dustbin gets opened when a person comes in range of 30cm in front of the dustbin
*/

#include   //INCLUDES SERVO LIBRARY

Servo servo;
int trigPin = 5;
int echoPin = 6;
int servoPin = 9;
long duration, distance, average;
long averDist[3];

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo.write(0); //CLOSES CAP ON STARTING
  delay(100);
  servo.detach();
}

void measure() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1; //CALCULATES DISTANCE
}

void loop() {
  Serial.println(distance);   
  for (int i = 0; i <= 2; i++) { //CALCULATES AVERAGE DISTANCE
    measure();
    averDist[i] = distance;
    delay(10);
  }
  distance = (averDist[0] + averDist[1] + averDist[2]) / 3;

  if ( distance <= 30 ) {
    servo.attach(servoPin);
    delay(1);
    servo.write(180);
    delay(3500);
  }
  else
    servo.write(0);
    delay(1500);

    servo.detach();

}
 
