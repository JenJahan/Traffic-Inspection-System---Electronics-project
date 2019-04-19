#include <Servo.h>

int i;

int servoPin = 9;
int trigPin = 4;    // Trigger
int echoPin = 3;    // Echo
long duration, cm, inches;

Servo Servo1;

void setup()
{
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Servo1.attach(servoPin);
}

void loop()
{

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // Convert the time into a distance
  cm = (duration / 2) / 29.1;   // Divide by 29.1 or multiply by 0.0343
  inches = (duration / 2) / 74; // Divide by 74 or multiply by 0.0135

  if (cm < 18)
  {
    digitalWrite(2,HIGH);
    delay(100);
    digitalWrite(2,LOW);
    for (i = 0; i < 1; i++)
    {
      for (int j = 0; j <= 1; j++) {
        if (cm < 18) {
          digitalWrite(2,HIGH);
          delay(1000);
          digitalWrite(2,LOW);
          delay(5000);
          digitalWrite(trigPin, LOW);
          delayMicroseconds(5);
          digitalWrite(trigPin, HIGH);
          delayMicroseconds(10);
          digitalWrite(trigPin, LOW);
          pinMode(echoPin, INPUT);
          duration = pulseIn(echoPin, HIGH);

          // Convert the time into a distance
          cm = (duration / 2) / 29.1;   // Divide by 29.1 or multiply by 0.0343
          inches = (duration / 2) / 74; // Divide by 74 or multiply by 0.0135
        } else {
          break;
        }
      }
      
      if (cm < 18)
      {
        // Make servo go to 0 degrees
        //delay(5000);
        Servo1.write(0);
        delay(3000);
        // Make servo go to 90 degrees
        Servo1.write(90);
      }
      else
        break;
    }
  }
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(200);
}
