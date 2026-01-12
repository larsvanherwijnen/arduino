#include "Utils.h"

String urlDecode(const String &input) {
    String decoded = "";
    char temp[] = "0x00";

    for (unsigned int i = 0; i < input.length(); i++) {
        char c = input.charAt(i);

        if (c == '+') {
            decoded += ' ';
        }
        else if (c == '%' && i + 2 < input.length()) {
            temp[2] = input.charAt(i + 1);
            temp[3] = input.charAt(i + 2);
            decoded += (char) strtol(temp, nullptr, 16);
            i += 2;
        }
        else {
            decoded += c;
        }
    }

    return decoded;
}
