/*
    Simple calculator.
    
    He can add, subtract, multiply and divide numbers.
    The entered numbers and the result are displayed on the LCD screen.

    To work, you need a 4x4 matrix keyboard and a 1602 LCD screen.
    Assignment of keyboard buttons:

        1 2 3 +
        4 5 6 -
        7 8 9 *
        C 0 = /

    (C is clear)

    This example is based on the library "Arduino-Keypad"
    GitHub: https://github.com/kurskov/Arduino-Keypad

    Author: Dmitrii Kurskov <dmitrii@kurskov.ru>
    Version: 1.0.0
    MIT license
*/


#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Include the keypad library.
#include "Keypad.h"

// If you are not using a port monitor, comment out the following line.
#define DEBUG_ON

const uint8_t row = 4;                          // number of rows
const uint8_t col = 4;                          // number of colums
uint8_t row_pins[] = {11, 10, 9, 8};            // Arduino pins for rows connected
uint8_t col_pins[] = {7, 6, 5, 4};              // Arduino pins for colums connected

char keys[row][col] = {{'1', '2', '3', '+'},    // keypad symbols
                       {'4', '5', '6', '-'},
                       {'7', '8', '9', '*'},
                       {'c', '0', '=', '/'}};

LiquidCrystal_I2C lcd(0x27, 16, 2);                             // LCD
Keypad<char> kp(row, col, (char*)keys, row_pins, col_pins);     // keypad

char action;                                    // math operator
String mem_number = "0";                        // memorized number
String work_number = "0";                       // working number

void setup() {
    #ifdef DEBUG_ON
        Serial.begin(9600);
    #endif
    
    lcd.init();
    lcd.backlight();
    lcd.setCursor(4,0);
	lcd.print("EasyCalc");
	lcd.setCursor(3,1);
	lcd.print("ver. 1.0.0");
	delay(2000);
	showWorkNumber();                           // show 0 on the LCD screen
}

void loop() {
    char key = kp.getKey();                     // scanning of key pressing
    if (key) {
        selectAction(key);
        #ifdef DEBUG_ON
            Serial.print("Key: "); Serial.print(key);
            Serial.print("; safeV: "); Serial.print(mem_number);
            Serial.print("; bufV: "); Serial.print(work_number);
            Serial.print("; action: "); Serial.println(action);
        #endif
    }
}

void selectAction(const char key) {
    if (key == '+' or key == '-' or key == '*' or key == '/') {
        if (mem_number != "0") getResult();
        mem_number = work_number;
        work_number = "0";
        action = key;
    } else {
        switch(key) {
            case 'c':
                mem_number = "0";
                work_number = "0";
                showWorkNumber();
                break;
            case '=':
                getResult();
                mem_number = work_number;
                work_number = "0";
                action = '\0';
                break;
            default:
                if (work_number == "0") work_number = "";
                work_number += key;
                showWorkNumber();
                break;
        }
    }
}

// Performs a mathematical operation on two numbers, 
// where the first number in the formula is mem_number 
// and the second is work_number.
// Result saved in working number and show on LCD screen.
void getResult() {
    switch (action) {
        case '+':
            work_number = String(mem_number.toInt() + work_number.toInt());
            break;
        case '-':
            work_number = String(mem_number.toInt() - work_number.toInt());
            break;
        case '*':
            work_number = String(mem_number.toInt() * work_number.toInt());
            break;
        case '/':
            work_number = String(mem_number.toInt() / work_number.toInt());
            break;
    }
    showWorkNumber();
}

// Clears screen and show data from work_number variable in the top left.
// Cursor position calculate from length of the string variable.
void showWorkNumber() {
    lcd.clear();
    lcd.setCursor(16 - work_number.length(),0);
    lcd.print(work_number);
}
