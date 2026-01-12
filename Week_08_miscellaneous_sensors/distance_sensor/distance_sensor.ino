#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 8;

// LED pins
const int greenLED = 5;
const int yellowLED = 6;
const int redLED = 7;

float duration, distance;  

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Setup LED pins
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("SSD1306 init failed");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  // Measure distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH, 30000);
  distance = (duration * .0343) / 2;

  
  // Check if reading is valid
  if (distance > 0 && distance <= 200) {
    Serial.print("Distance: ");
    Serial.println(distance);
    updateDisplay(distance);
    // LED and Buzzer logic based on distance
    if (distance <= 10) {
      // DANGER ZONE - Red LED, continuous beep
      digitalWrite(greenLED, LOW);
      digitalWrite(yellowLED, LOW);
      digitalWrite(redLED, HIGH);
      tone(buzzerPin, 2000);
    }
    else if (distance <= 20) {
      // Very close - Red LED, fast beeping
      digitalWrite(greenLED, LOW);
      digitalWrite(yellowLED, LOW);
      digitalWrite(redLED, HIGH);
      tone(buzzerPin, 1500, 100);
      delay(100);
    }
    else if (distance <= 50) {
      // Caution zone - Yellow LED, medium beeping
      digitalWrite(greenLED, LOW);
      digitalWrite(yellowLED, HIGH);
      digitalWrite(redLED, LOW);
      tone(buzzerPin, 1200, 100);
      delay(200);
    }
    else if (distance <= 100) {
      // Safe but aware - Green LED, slow beeping
      digitalWrite(greenLED, HIGH);
      digitalWrite(yellowLED, LOW);
      digitalWrite(redLED, LOW);
      tone(buzzerPin, 1000, 100);
      delay(400);
    }
    else {
      // All clear - Green LED, no beep
      digitalWrite(greenLED, HIGH);
      digitalWrite(yellowLED, LOW);
      digitalWrite(redLED, LOW);
      noTone(buzzerPin);
    }
  }
  else {
    // Out of range - All LEDs off
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
    noTone(buzzerPin);
    Serial.println("Out of range");
  }
  
  delay(50);
}

void updateDisplay(float distance) {
  display.clearDisplay();
  display.setCursor(0, 0);

  display.print(distance, 1);  
  display.println(" CM");

  display.display();          
}