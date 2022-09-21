/*
    Keypads library
    
    Author: Dmitrii Kurskov <dmitrii@kurskov.ru>
    GitHub: https://github.com/kurskov/Arduino-Keypad
    Version: 1.0.0
    MIT license
*/

#ifndef _DK_Keypad_h
#define _DK_Keypad_h

#include <Arduino.h>

#define KP_DEBOUNCE 10

template < typename TYPE >
class Keypad {
    public:
        Keypad(uint8_t rows, uint8_t cols, TYPE *keys, uint8_t *row_pins, uint8_t *col_pins) {
            _rows = rows;
            _cols = cols;
            _keys = keys;
            _row_pins = row_pins;
            _col_pins = col_pins;

            for (uint8_t i = 0; i < _rows; i++) {
                pinMode(_row_pins[i], INPUT_PULLUP);
            }
            
            for (uint8_t i = 0; i < _cols; i++) {
                pinMode(_col_pins[i], INPUT_PULLUP);
            }
        }
        
        TYPE getPressedKey() {
            _key = '\0';
            for (uint8_t col = 0; col < _cols; col++) {
                pinMode(_col_pins[col], OUTPUT);
                digitalWrite(_col_pins[col], LOW);            
                for (uint8_t row = 0; row < _rows; row++) {
                    if (!digitalRead(_row_pins[row])) {
                        _key = _keys[row * _cols + col];
                    }
                }
                pinMode(_col_pins[col], INPUT_PULLUP);
            }
            return _key;
        }

        TYPE getKey() {
            if (millis() - _timer > _keyDebounce) {
                _timer = millis();
                _key = getPressedKey();
                if (_key && !_keyHold) {
                    _keyHold = 1;
                    return _key;
                } else if (!_key) {
                    _keyHold = 0;
                }
            }
            return '\0';
        }

        void setDebounce(uint8_t ms) {
            _keyDebounce = ms;
        }


    private:
        uint8_t _rows;
        uint8_t _cols;
        
        uint8_t *_row_pins;
        uint8_t *_col_pins;
        TYPE *_keys;
        
        TYPE _key;
        uint8_t _keyDebounce = KP_DEBOUNCE;
        uint8_t _keyHold = 0;
        uint16_t _timer;
};

#endif // _DK_Keypad_h
