#include "WiFiManager.h"
#include "EEPROMHelper.h"
#include "Utils.h"

// ---------------------- Wi-Fi helpers ----------------------
bool connectToSavedWiFi() {
  String ssid = readStringFromEEPROM(SSID_ADDR, MAX_SSID_LEN);
  String pass = readStringFromEEPROM(PASS_ADDR, MAX_PASS_LEN);

  if (ssid.length() == 0) return false;

  WiFi.begin(ssid.c_str(), pass.c_str());

  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - start > 10000) return false;  // 10s timeout
    delay(500);
  }

  return true;
}


String wifiScanDropdown() {
  int n = WiFi.scanNetworks();
  struct Network {
    String ssid;
    int rssi;
  };

  // Temporary array to store unique networks
  Network uniqueNetworks[n];
  int uniqueCount = 0;

  for (int i = 0; i < n; i++) {
    String currentSSID = WiFi.SSID(i);
    int currentRSSI = WiFi.RSSI(i);
    bool found = false;

    // Check if we already added this SSID
    for (int j = 0; j < uniqueCount; j++) {
      if (uniqueNetworks[j].ssid == currentSSID) {
        found = true;
        // Keep the stronger signal
        if (currentRSSI > uniqueNetworks[j].rssi) {
          uniqueNetworks[j].rssi = currentRSSI;
        }
        break;
      }
    }

    if (!found) {
      uniqueNetworks[uniqueCount].ssid = currentSSID;
      uniqueNetworks[uniqueCount].rssi = currentRSSI;
      uniqueCount++;
    }
  }

  // Build the HTML dropdown
  String html = "<select name='ssid'>";
  for (int i = 0; i < uniqueCount; i++) {
    html += String("<option value='") + uniqueNetworks[i].ssid + "'>"
            + uniqueNetworks[i].ssid
            + "</option>";
  }
  html += "</select>";
  return html;
}


// ---------------------- Web request handling ----------------------
void handleWifiClient(WiFiClient &client) {
  // Wait until the client sends some data
  while (!client.available()) {
    delay(1);
  }

  String request = client.readStringUntil('\r');
  client.flush();

  // Simple route parsing
  if (request.indexOf("GET / ") >= 0) {
    // Serve root page
    String page = "<html><head><title>Wi-Fi Setup</title><style>"
                  "body{font-family:system-ui;background:#f3f4f6;padding:20px;}"
                  ".card{background:white;padding:20px;border-radius:10px;max-width:400px;margin:auto;}"
                  "h2{margin-top:0;}label{display:block;margin-top:10px;}"
                  "button{margin-top:15px;background:#2563eb;color:white;border:none;padding:10px;width:100%;border-radius:6px;font-size:16px;}"
                  "</style></head><body><div class='card'><h2>Wi-Fi Setup</h2>"
                  "<form method='POST' action='/'><label>Network</label>";
    page += wifiScanDropdown();
    page += "<label>Password</label><input type='password' name='pass' required>"
            "<button>Save</button></form></div></body></html>";

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println(page);

  } else if (request.indexOf("POST /") >= 0) {
    // Read POST data (naive, small payloads)
    String postData = client.readString();
    Serial.print(postData);

    String ssid, pass;
    int ssidIndex = postData.indexOf("ssid=");
    int passIndex = postData.indexOf("pass=");


    if (ssidIndex >= 0) {
      int end = postData.indexOf('&', ssidIndex);
      ssid = postData.substring(ssidIndex + 5, end >= 0 ? end : postData.length());
      ssid = urlDecode(ssid);
    }

    if (passIndex >= 0) {
      int end = postData.indexOf('&', passIndex);
      pass = postData.substring(passIndex + 5, end >= 0 ? end : postData.length());
      pass = urlDecode(pass);
    }

    String page =
      "<html><head><title>Wi-Fi Setup</title><style>"
      "body{font-family:system-ui;background:#f3f4f6;padding:20px;}"
      ".card{background:white;padding:20px;border-radius:10px;max-width:400px;margin:auto;}"
      "h2{margin-top:0;}"
      "p{margin-top:10px;line-height:1.4;}"
      "</style></head><body>"
      "<div class='card'>"
      "<h2>Wi-Fi Setup</h2>"
      "<p><strong>Wi-Fi credentials received!</strong><br>"
      "Trying to connect to the network.</p>"
      "<p>1. If the <strong>red light</strong> is still on after 5 seconds, the password was incorrect."
      "<p>2. If the <strong>orange light</strong> turns on, "
      "the device has successfully connected to the network.</p>"
      "<i>If the connection fails, reconnect to the Cloud network to try again.</i>"
      "</div></body></html>";

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println(page);
    delay(1000);

    WiFi.begin(ssid.c_str(), pass.c_str());

    unsigned long start = millis();
    bool connected = false;
    while (millis() - start < 10000) {
      if (WiFi.status() == WL_CONNECTED) {
        connected = true;
        break;
      }
      delay(1000);
    }

    if (connected) {
      writeStringToEEPROM(SSID_ADDR, ssid, MAX_SSID_LEN);
      writeStringToEEPROM(PASS_ADDR, pass, MAX_PASS_LEN);
    }

    NVIC_SystemReset();
  }

  client.stop();
}
