/*on start picks up object, follows person until stopped, drops item, idle.*/
#include <Servo.h>
int sensorServoPin = 4;
int armServoPin = 3;
Servo sensorServo; //initialize servo
Servo armServo;
int echoPin = 8;
int trigPin = 7;
int distance = 0;
int motor1 = 5;
int motor2 = 6;
int motor3 = 9;
int motor4 = 10;
int turnDelay = 10; 
int upper = 360; 
int lower = 0; 
int stopCounter = 0;

void TurnRight(){ //Turn right
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, HIGH);
  delay(turnDelay);
  Stop();
}
void TurnLeft(){ //Turn left
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, LOW);
  delay(turnDelay);
  Stop();
}
void Lower(){ //Lower arm
  for (int i = upper; i>lower;i-=6){
    sensorServo.write(i);
    delay(10);
  }
}
void Lift(){ //Lift arm
  for (int i = lower; i<upper;i+=6){
    sensorServo.write(i);
    delay(10);
  }
}
void Forward(){ //Makes the car move forward
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, HIGH); 
}
void Reverse(){ //Makes the car back up
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, LOW); 
}
void Stop(){ //Stops the car
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, LOW); 
}
void ReadDistance(){ //Reads distance on command
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  distance = pulseIn(echoPin, HIGH);
  distance = distance / 58;
  Serial.print("The distance is : ");
  Serial.print(distance);
  Serial.print(" cm\n");
}

void setup(){
  Serial.begin(9600);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
  pinMode(sensorServoPin, OUTPUT);
  sensorServo.attach(sensorServoPin);
  
  sensorServo.write(upper);
  Stop();

  //Picks up object before following person
  Lower();
  Forward();
  delay(1000);
  Stop();
  Lift();
}

void loop(){
  ReadDistance();
  if (distance < 20){
    Reverse();
  }
  else if (distance < 40){
    stopCounter = 1;
    Stop();
    while((distance < 40) && (distance > 20) && (stopCounter < 50)){
      ReadDistance();
      delay(100);
      stopCounter++;
      if (stopCounter == 100){
        Lower();
        delay(30000);
        Lift();
      }
    }
  }
  else if (distance <= 60){
    Forward();
  }
  else if (distance > 60){ //If distance is greater than 30, continuously look left and right something.
    TurnLeft();
    delay(100);
    ReadDistance;
    delay(200);
    if (distance < 60){TurnLeft(); TurnLeft(); TurnLeft();}
    TurnRight; TurnRight();
    delay(100);
    ReadDistance;
    delay(200);
  }
  delay(100);
}
