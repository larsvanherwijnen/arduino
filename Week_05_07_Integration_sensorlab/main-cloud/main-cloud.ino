#include <WiFiS3.h>
#include <EEPROM.h>
#include "WiFiManager.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "ConfigManager.h"
#include "EEPROMHelper.h"

// 🔹 Job system
#include "JobFactory.h"
#include "MqttManager.h"

// --------------------------------------------------
// Pins & Config
// --------------------------------------------------

#define RESET_BUTTON_PIN 0
#define WIFI_CONNECTED_LIGHT 12

#define AP_NAME "Cloud-Setup"
#define AP_PASS "setup1234"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
WiFiServer server(80);

// --------------------------------------------------
// WiFi state machine
// --------------------------------------------------

enum WifiState {
  WIFI_BOOT,
  WIFI_AP_MODE,
  WIFI_CONNECTING,
  WIFI_CONNECTED
};

WifiState wifiState = WIFI_BOOT;
WifiState lastWifiState = WIFI_BOOT;

IPAddress lastIP;

// --------------------------------------------------
// Job runtime
// --------------------------------------------------

JobBase* currentJob = nullptr;
bool jobStarted = false;

// --------------------------------------------------
// Helpers
// --------------------------------------------------

bool waitForIP(unsigned long timeoutMs = 10000) {
  unsigned long start = millis();
  while (WiFi.localIP() == IPAddress(0, 0, 0, 0)) {
    if (millis() - start > timeoutMs) return false;
    delay(100);
  }
  return true;
}

// --------------------------------------------------
// Setup
// --------------------------------------------------

void setup() {
  Serial.begin(9600);
  EEPROM.begin();

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(WIFI_CONNECTED_LIGHT, OUTPUT);
  pinMode(RESET_BUTTON_PIN, INPUT_PULLUP);

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("SSD1306 init failed");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Factory reset on boot
  if (digitalRead(RESET_BUTTON_PIN) == LOW) {
    resetWiFiCredentials();
  }

  wifiState = WIFI_CONNECTING;
  updateDisplay();

  // ---------------- WiFi connect ----------------

  if (connectToSavedWiFi()) {

    if (waitForIP()) {
      wifiState = WIFI_CONNECTED;
      digitalWrite(WIFI_CONNECTED_LIGHT, HIGH);
      server.begin();

      Serial.print("Connected IP: ");
      Serial.println(WiFi.localIP());

    } else {
      Serial.println("DHCP timeout, switching to AP mode");
      WiFi.disconnect();
      wifiState = WIFI_AP_MODE;
    }

  } else {
    wifiState = WIFI_AP_MODE;
  }

  // ---------------- AP mode ----------------

  if (wifiState == WIFI_AP_MODE) {
    WiFi.beginAP(AP_NAME, AP_PASS);
    server.begin();
    digitalWrite(LED_BUILTIN, HIGH);

    Serial.print("AP mode IP: ");
    Serial.println(WiFi.localIP());
  }

  updateDisplay();
}

// --------------------------------------------------
// Loop
// --------------------------------------------------

void loop() {

  // Long press reset (2s)
  if (digitalRead(RESET_BUTTON_PIN) == LOW) {
    delay(2000);
    if (digitalRead(RESET_BUTTON_PIN) == LOW) {
      resetWiFiCredentials();
    }
  }

  // Web server handling
  WiFiClient client = server.available();
  if (client) {
    if (wifiState == WIFI_AP_MODE) {
      handleWifiClient(client);
    } else if (wifiState == WIFI_CONNECTED) {
      handleConfigClient(client);
    }
  }

  // Update display on state change
  if (wifiState != lastWifiState) {
    lastWifiState = wifiState;
    updateDisplay();
  }

  // Update display when IP changes
  if (wifiState == WIFI_CONNECTED && WiFi.localIP() != lastIP) {
    lastIP = WiFi.localIP();
    updateDisplay();
  }

  // --------------------------------------------------
  // Job + MQTT startup (only once)
  // --------------------------------------------------

  if (wifiState == WIFI_CONNECTED && !jobStarted) {

    JobType jobType = getJob();
    currentJob = createJob(jobType);

    if (currentJob) {
      Serial.print("Starting job: ");
      Serial.println(jobTypeToString(jobType));

      currentJob->setup();
      mqttSetup(currentJob);
      jobStarted = true;
    } else {
      Serial.println("No valid job configured");
    }
  }

  // --------------------------------------------------
  // Run job + MQTT
  // --------------------------------------------------

  if (currentJob) {
    currentJob->loop();
  }

  mqttLoop();
}

// --------------------------------------------------
// OLED Display
// --------------------------------------------------

void updateDisplay() {
  display.clearDisplay();
  display.setCursor(0, 0);

  switch (wifiState) {

    case WIFI_CONNECTED: {
      display.print("IP: ");
      display.println(WiFi.localIP());

      JobType currentJob = getJob();
      display.print("Job: ");
      display.println(jobTypeToString(currentJob));
      break;
    }

    case WIFI_AP_MODE:
      display.println("AP MODE");
      display.println();
      display.print("SSID: ");
      display.println(AP_NAME);
      display.println();
      display.print("IP: ");
      display.println(WiFi.localIP());
      break;

    case WIFI_CONNECTING:
      display.println("CONNECTING...");
      display.println();
      display.println("Trying saved WiFi");
      break;

    default:
      display.println("BOOTING...");
      break;
  }

  display.display();
}

// --------------------------------------------------
// Reset WiFi Credentials
// --------------------------------------------------

void resetWiFiCredentials() {
  Serial.println("Clearing Wi-Fi credentials");

  writeStringToEEPROM(SSID_ADDR, "", MAX_SSID_LEN);
  writeStringToEEPROM(PASS_ADDR, "", MAX_PASS_LEN);

  delay(1000);
  NVIC_SystemReset();
}
