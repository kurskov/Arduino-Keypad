/*
    Keypads library
    
    Author: Dmitrii Kurskov <dmitrii@kurskov.ru>
    GitHub: https://github.com/kurskov/Arduino-Keypad
    Version: 0.1.0
    MIT license
*/

#ifndef _DK_Keypad_h
#define _DK_Keypad_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include <Arduino.h>
#else
    #include <WProgram.h>
#endif

class Keypad {
    public:
        Keypad();

    private:
    
};

#endif // _DK_Keypad_h