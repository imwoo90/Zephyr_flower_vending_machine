#ifndef KEYPAD_4X3_H
#define KEYPAD_4X3_H

#include <functional>
#include <Keypad.h>
#include <PCF8574.h>

class Keypad_4x3 : public Keypad {
private:
    PCF8574 pcf8574;
    Keypad_4x3(char *userKeymap, byte *row, byte *col, byte numRows, byte numCols);
public:
    virtual void pin_mode(byte pinNum, byte mode);
    virtual void pin_write(byte pinNum, boolean level);
    virtual int  pin_read(byte pinNum);

    static Keypad_4x3* getInstance();
    void onLED();
    void offLED();
    void subscribe(std::function<void(const KeyState, const char)> callback);
};


#endif