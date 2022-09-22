[![GitHub](https://img.shields.io/github/license/kurskov/Arduino-Keypad)](https://github.com/kurskov/Arduino-Keypad/blob/main/LICENSE)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/kurskov/Arduino-Keypad)](https://github.com/kurskov/Arduino-Keypad/releases/latest)

# Keypad

This is a small Arduino library for using matrix keypads. 

Keypad library is based on the [SimpleKeypad](https://github.com/maximebohrer/SimpleKeypad).

## How to use

### Include library

```c++
#include "Keypad.h"
```

### Initialization

```c++
Keypad<char> motor(ROWS, COLS, (char*)KEYS, ROW_PINS, COL_PINS);
```

ROWS - number of keyboard rows  
COLS - number of keyboard columns  
KEYS - two-dimensional array with button values  
ROW_PINS - array with Arduino pins for rows connected  
COL_PINS - array with Arduino pins for columns connected  

### Basic function

<TYPE> getPressedKey() - 
<TYPE> getKey() - 
<TYPE> setDebounce() - 

## Example

```c++
#include <Wire.h>
#include "Keypad.h"

const uint8_t row = 4;
const uint8_t col = 4;
uint8_t row_pins[] = {11, 10, 9, 8};
uint8_t col_pins[] = {7, 6, 5, 4};
char keys[row][col] = {{'1', '2', '3', 'A'},
                       {'4', '5', '6', 'B'},
                       {'7', '8', '9', 'C'}, 
                       {'*', '0', '#', 'D'}};

Keypad<char> kp(row, col, (char*)keys, row_pins, col_pins);

void setup() {
    Serial.begin(9600);
}

void loop() {
    char key = kp.getKey();
    if (key) {
        Serial.println(key);
    }
}
```

## If you find bugs
When you find bugs, create an issue, or write to the mail info@kurskov.ru.  
The library is open for revision and your pull requests.

## License
Keypad by [Dmitrii Kurskov](https://kurskov.ru) is licensed under a MIT License.
