#include "EEPROMHelper.h"
#include <EEPROM.h>

// ------------------------ Read string from EEPROM ------------------------
String readStringFromEEPROM(int addr, int maxLen) {
    String result;
    for (int i = 0; i < maxLen; i++) {
        char c = EEPROM.read(addr + i);
        if (c == 0) break;  // null-terminated
        result += c;
    }
    return result;
}

// ------------------------ Write string to EEPROM -----------------------
void writeStringToEEPROM(int addr, const String &value, int maxLen) {
    for (int i = 0; i < maxLen; i++) {
        char c = (i < value.length()) ? value[i] : 0;
        EEPROM.write(addr + i, c);
    }
}
