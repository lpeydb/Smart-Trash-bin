#include <Arduino.h>
#include <Servo.h>
#define echoPin 2  // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3  // attach pin D3 Arduino to pin Trig of HC-SR04
Servo servo_pin_9; //舵机名称
// defines variables
long duration; // variable for the duration of sound wave travel
int distance;  // variable for the distance measurement
int angle = 0; //舵机角度

void setup()
{
  pinMode(trigPin, OUTPUT);                         // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);                          // Sets the echoPin as an INPUT
  servo_pin_9.attach(9);                            //控制舵机信号引脚
  Serial.begin(9600);                               // // Serial Communication is starting with 9600 of baudrate speed
}
void loop()
{
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  if (distance < 20)
  {
    if (servo_pin_9.read() == 90)
    {
      delay(1000);
    }
    else
    {
      angle = servo_pin_9.read();
      while (angle < 90)  //缓慢打开垃圾桶
      {
        angle++;
        servo_pin_9.write(angle);
        delay(10);
      }
      delay(1000);
    }
  }
  else
  {
    if (servo_pin_9.read() == 0)
    {
      delay(200);
    }
    else
    {
      angle = servo_pin_9.read();
      while (angle > 0)  //缓慢关闭垃圾桶
      {
        angle--;
        servo_pin_9.write(angle);
        delay(10);
      }
      servo_pin_9.write(0);
    }
  }
}
