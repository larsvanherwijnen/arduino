#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display instellingen
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Force sensor pin
const int forcePin = A0;

void setup() {
  Serial.begin(9600);
  
  // OLED initialiseren
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 niet gevonden"));
    for(;;);
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Force Sensor");
  display.display();
  delay(2000);
}

void loop() {
  int forceValue = analogRead(forcePin);
  
  int forcePercent = map(forceValue, 0, 1023, 0, 100);
  
  display.clearDisplay();
  
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Kracht Meting:");
  
  display.setTextSize(3);
  display.setCursor(10, 20);
  display.print(forcePercent);
  display.println("%");
  
  display.setTextSize(1);
  int barWidth = map(forceValue, 0, 1023, 0, 118);
  display.fillRect(5, 52, barWidth, 8, SSD1306_WHITE);
  display.drawRect(5, 52, 118, 8, SSD1306_WHITE);
  
  display.display();
  
  delay(50);
}