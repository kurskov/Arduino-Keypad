#include <Wire.h>

#include "Keypad.h"

const int row = 4;
const int col = 4;
int row_pins[] = {11, 10, 9, 8};
int col_pins[] = {7, 6, 5, 4};
char keys[row][col] = {{'1', '2', '3', 'A'},{'4', '5', '6', 'B'},{'7', '8', '9', 'C'},{'*', '0', '#', 'D'}};

Keypad kp(row, col, (char*)keys, row_pins, col_pins);

void setup() {
    Serial.begin(9600);
}

void loop() {
    char key = kp.getKey();
    if (key) {
        Serial.println(kp.getKey());
    }
}
