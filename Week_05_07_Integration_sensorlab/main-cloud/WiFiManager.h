#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <WiFiS3.h>
#include <EEPROM.h>
// Function declarations
bool connectToSavedWiFi();
String wifiScanDropdown();
void handleWifiClient(WiFiClient &client);

#endif
