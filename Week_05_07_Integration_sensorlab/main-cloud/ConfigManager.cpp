#include <WiFiS3.h>
#include <R4HttpClient.h>
#include "EEPROMHelper.h"
#include "Utils.h"
#include <ArduinoJson.h>
#include "ConfigManager.h"

WiFiSSLClient sslClient;

// =====================================================
// Job definitions
// =====================================================
const JobType allJobs[] = {
  JOB_NONE,
  JOB_PRINT_TASK,
  JOB_PRINT_FEELINGS,
  JOB_CONTROL_LEDS
};

const int NUM_JOBS = sizeof(allJobs) / sizeof(allJobs[0]);

const char* jobTypeToString(JobType job) {
  switch (job) {
    case JOB_NONE: return "Kies een taak";
    case JOB_PRINT_TASK: return "Task printer";
    case JOB_PRINT_FEELINGS: return "Wolk status printer";
    case JOB_CONTROL_LEDS: return "Wolk Leds";
    default: return "Unknown";
  }
}

// =====================================================
// EEPROM access
// =====================================================
String getRoomID() {
  return readStringFromEEPROM(ROOM_ID_ADDR, MAX_ROOM_LEN);
}

void setRoomID(const String& roomID) {
  writeStringToEEPROM(ROOM_ID_ADDR, roomID, MAX_ROOM_LEN);
}

JobType getJob() {
  uint8_t value = EEPROM.read(JOB_ADDR);
  if (value >= NUM_JOBS) return JOB_NONE;
  return (JobType)value;
}

void setJob(JobType job) {
  EEPROM.write(JOB_ADDR, (uint8_t)job);
}

// =====================================================
// Fetch rooms for dropdown (HTML)
// =====================================================
String fetchRoomsDropdown() {
  String selectedRoom = getRoomID();
  String html = "<select name='room'>";

  if (WiFi.status() != WL_CONNECTED) {
    html += "<option>No Wi-Fi</option></select>";
    return html;
  }

  R4HttpClient http;
  http.begin(sslClient, "https://api-sensorlab.larsvanherwijnen.nl/api/rooms", 443);
  http.setTimeout(5000);
  http.addHeader("User-Agent: Arduino UNO R4 WiFi");
  http.addHeader("Connection: close");

  int responseCode = http.GET();
  if (responseCode > 0) {
    String payload = http.getBody();
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, payload);

    // Placeholder
    html += "<option value='0'";
    if (selectedRoom.isEmpty()) html += " selected";
    html += ">Kies een kamer</option>";

    if (!error && doc.is<JsonArray>()) {
      for (JsonObject room : doc.as<JsonArray>()) {
        const char* id = room["id"];
        const char* name = room["name"];
        const char* code = room["code"];

        html += "<option value='" + String(id) + "'";
        if (selectedRoom == id) html += " selected";
        html += ">" + String(name) + " (" + String(code) + ")" + "</option>";
      }
    } else {
      html += "<option>Failed to parse rooms</option>";
    }
  } else {
    html += "<option>Failed to fetch rooms</option>";
  }

  http.close();
  html += "</select>";
  return html;
}

// =====================================================
// Fetch job dropdown (HTML)
// =====================================================
String fetchJobDropdown() {
  JobType currentJob = getJob();
  String html = "<select name='job'>";

  for (int i = 0; i < NUM_JOBS; i++) {
    JobType job = allJobs[i];
    html += "<option value='" + String(job) + "'";
    if (job == currentJob) html += " selected";
    html += String(">") + jobTypeToString(job) + "</option>";
  }

  html += "</select>";
  return html;
}

// =====================================================
// Web client handler
// =====================================================
void handleConfigClient(WiFiClient& client) {
  while (!client.available()) delay(1);
  String request = client.readStringUntil('\r');
  client.flush();

  // ---------------- GET ----------------
  if (request.indexOf("GET / ") >= 0) {
    String page =
      "<html><head><title>Device Configuration</title>"
      "<style>"
      "body{font-family:system-ui;background:#f3f4f6;padding:20px;}"
      ".card{background:white;padding:24px;border-radius:12px;"
      "max-width:420px;margin:auto;box-shadow:0 10px 20px rgba(0,0,0,.08);}"
      "h2{margin:0 0 16px 0;}"
      ".section{margin-top:16px;}"
      "label{display:block;font-weight:600;margin-bottom:6px;}"
      "select{width:100%;padding:10px;border-radius:6px;border:1px solid #d1d5db;}"
      "button{margin-top:24px;background:#2563eb;color:white;border:none;"
      "padding:12px;width:100%;border-radius:8px;font-size:16px;cursor:pointer;}"
      "</style></head><body>"
      "<div class='card'>"
      "<h2>Device Configuration</h2>"
      "<form method='POST' action='/'>"

      "<div class='section'><label>Room</label>";
    page += fetchRoomsDropdown();

    page += "</div><div class='section'><label>Device Job</label>";
    page += fetchJobDropdown();

    page += "</div><button>Save Configuration</button></form></div></body></html>";

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println(page);
  }

  // ---------------- POST ----------------
  else if (request.indexOf("POST /") >= 0) {
    String postData = client.readString();
    Serial.println(postData);

    String roomID;
    JobType job = JOB_NONE;

    // Extract room
    int roomIdx = postData.indexOf("room=");
    if (roomIdx >= 0) {
      int end = postData.indexOf('&', roomIdx);
      roomID = postData.substring(roomIdx + 5, end >= 0 ? end : postData.length());
      roomID = urlDecode(roomID);
      setRoomID(roomID);
    }

    // Extract job
    int jobIdx = postData.indexOf("job=");
    if (jobIdx >= 0) {
      int end = postData.indexOf('&', jobIdx);
      job = (JobType)postData.substring(jobIdx + 4, end >= 0 ? end : postData.length()).toInt();
      setJob(job);
    }

    String page =
      "<html><body>"
      "<h2>Configuration Saved</h2>"
      "<p><b>Room:</b> "
      + roomID + "</p>"
                 "<p><b>Job:</b> "
      + String(jobTypeToString(job)) + "</p>"
                                       "</body></html>";

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println(page);
  }

  delay(5);
  client.stop();
}
