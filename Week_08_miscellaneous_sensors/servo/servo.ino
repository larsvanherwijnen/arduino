#include <Servo.h>

Servo myservo;

// Pin configuratie
const int servoPin = 9;
const int buttonLeft = 2;
const int buttonRight = 3;

int position = 90; // Start positie (midden)

void setup() {
  myservo.attach(servoPin);
  myservo.write(position);
  
  pinMode(buttonLeft, INPUT_PULLUP);
  pinMode(buttonRight, INPUT_PULLUP);
  
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(buttonLeft) == LOW) {
    position -= 2; 
    if (position < 0) position = 0;
    myservo.write(position);
    Serial.print("Positie: ");
    Serial.println(position);
    delay(20); 
  }
  
  if (digitalRead(buttonRight) == LOW) {
    position += 2;
    if (position > 180) position = 180;
    myservo.write(position);
    Serial.print("Positie: ");
    Serial.println(position);
    delay(20);
  }
}