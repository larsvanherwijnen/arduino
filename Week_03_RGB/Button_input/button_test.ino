#define BUTTON_PIN 2

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.println("Press the button...");
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    Serial.println("Button pressed!");
    delay(200); // simple debounce
  }
}