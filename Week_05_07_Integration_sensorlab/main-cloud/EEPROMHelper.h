#ifndef EEPROMHELPER_H
#define EEPROMHELPER_H

#include <EEPROM.h>
#include <Arduino.h>

// EEPROM addresses
#define SSID_ADDR      0
#define PASS_ADDR      64
#define ROOM_ID_ADDR   128
#define JOB_ADDR       200  

// Max lengths
#define MAX_SSID_LEN   64
#define MAX_PASS_LEN   64
#define MAX_ROOM_LEN   40

// EEPROM read/write
String readStringFromEEPROM(int addr, int maxLen);
void writeStringToEEPROM(int addr, const String &value, int maxLen);

#endif
