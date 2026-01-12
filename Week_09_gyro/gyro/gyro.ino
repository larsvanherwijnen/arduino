#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

int dice[5] = {1, 1, 1, 1, 1};
bool shaking = false;
bool thrown = false;
unsigned long shakeStartTime = 0;

void setup() {
  Serial.begin(115200);
  
  Wire.begin();
  mpu.initialize();
  
  if (!mpu.testConnection()) {
    Serial.println("ERROR:MPU6050");
    while(1);
  }
  
  Serial.println("READY");
  randomSeed(analogRead(0));
}

void loop() {
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
  int totalMotion = abs(gx) + abs(gy) + abs(gz);
  
  // Detecteer schudden
  if (totalMotion > 15000 && !shaking) {
    shaking = true;
    shakeStartTime = millis();
    thrown = false;
    Serial.println("STATUS:SHAKING");
  }
  
  if (shaking && millis() - shakeStartTime < 2000) {
    for (int i = 0; i < 5; i++) {
      dice[i] = random(1, 7);
    }
    // Stuur data elke 100ms tijdens schudden
    if (millis() % 100 < 50) {
      sendDiceData();
    }
  }
  
  // Detecteer kantelen
  int16_t pitch = atan2(ay, az) * 180 / PI;
  
  if (shaking && pitch > 45 && !thrown) {
    thrown = true;
    shaking = false;
    
    // Definitieve worp
    for (int i = 0; i < 5; i++) {
      dice[i] = random(1, 7);
    }
    
    Serial.println("STATUS:THROWN");
    sendDiceData();
  }
  
  delay(50);
}

void sendDiceData() {
  Serial.print("DICE:");
  for (int i = 0; i < 5; i++) {
    Serial.print(dice[i]);
    if (i < 4) Serial.print(",");
  }
  Serial.println();
}