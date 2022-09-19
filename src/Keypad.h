/*
    Keypads library
    
    Author: Dmitrii Kurskov <dmitrii@kurskov.ru>
    GitHub: https://github.com/kurskov/Arduino-Keypad
    Version: 0.1.0
    MIT license
*/

#ifndef _DK_Keypad_h
#define _DK_Keypad_h

#include <Arduino.h>

// template < typename _TYPE >
class Keypad {
    public:
        Keypad(int rows, int cols, char *keys, int *row_pins, int *col_pins) {
            _rows = rows;
            _cols = cols;
            _keys = keys;
            _row_pins = row_pins;
            _col_pins = col_pins;

            for (int i = 0; i < _rows; i++) {
                pinMode(_row_pins[i], INPUT_PULLUP);
            }
            
            for (int i = 0; i < _cols; i++) {
                pinMode(_col_pins[i], INPUT_PULLUP);
            }
        }
        
        char getKey() {
            _key = '\0';
            for (int col = 0; col < _cols; col++) {
                pinMode(_col_pins[col], OUTPUT);
                digitalWrite(_col_pins[col], LOW);            
                for (int row = 0; row < _rows; row++) {
                    if (!digitalRead(_row_pins[row])) {
                        _key = _keys[row * _cols + col];
                    }
                }
                pinMode(_col_pins[col], INPUT_PULLUP);
            }
            return _key;
        }


    private:
        int _rows;
        int _cols;
        
        int *_row_pins;
        int *_col_pins;
        char *_keys;
        
        char _key;
};

#endif // _DK_Keypad_h
