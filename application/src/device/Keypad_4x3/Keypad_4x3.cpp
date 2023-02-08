#include "Keypad_4x3.h"
#include <vector>
#include <zephyr/drivers/gpio.h>

static const struct gpio_dt_spec led_key_pad = GPIO_DT_SPEC_GET(DT_NODELABEL(led_key_pad), gpios);
static std::vector<std::function<void(const KeyState, const char)> > _callbacks;

static void keypadEvent(KeypadEvent key){
    Keypad_4x3* kp = Keypad_4x3::getInstance();
    for (unsigned int i = 0; i < _callbacks.size(); i++) {
        _callbacks[i](kp->getState(), key);
    }
}

void Keypad_4x3::pin_mode(byte pinNum, byte mode) {
    // pcf8574.pinMode(pinNum, mode);
}
void Keypad_4x3::pin_write(byte pinNum, boolean level) {
    pcf8574.digitalWrite(pinNum, level);
}
int  Keypad_4x3::pin_read(byte pinNum) {
    int read = pcf8574.digitalRead(pinNum, true);
    return read;
}

Keypad_4x3::Keypad_4x3(char *userKeymap, byte *row, byte *col, byte numRows, byte numCols) :
    Keypad(userKeymap, row, col, numRows, numCols), pcf8574(0x20) {
    addEventListener(keypadEvent);
    for(int r = 0; r < numRows; r++)
        pcf8574.pinMode(row[r], INPUT_PULLUP);
    for(int c = 0 ; c < numCols; c++) {
        pcf8574.pinMode(col[c], OUTPUT);
        pcf8574.digitalWrite(col[c], HIGH);
    }

    //LED pin settings
    pcf8574.pinMode(P7, OUTPUT);

    pcf8574.begin();
    gpio_pin_configure_dt(&led_key_pad, GPIO_OUTPUT_INACTIVE);
}

Keypad_4x3* Keypad_4x3::getInstance() {
    static const byte _ROWS = 4; //four rows
    static const byte _COLS = 3; //three columns
    // static byte _rowPins[_ROWS] = {P0, P1, P2, P3}; //connect to the row pinouts of the keypad
    // static byte _colPins[_COLS] = {P6, P5, P4}; //connect to the column pinouts of the keypad
    static byte _rowPins[_ROWS] = {P6, P5, P4, P3};
    static byte _colPins[_COLS] = {P0, P1, P2};
    static char _keys[_ROWS][_COLS] = {
        {'1','2','3'},
        {'4','5','6'},
        {'7','8','9'},
        {'*','0','#'}
    };
    static Keypad_4x3* singleton_instance = NULL;

    if(singleton_instance == NULL) {
        singleton_instance = new Keypad_4x3(makeKeymap(_keys), _rowPins, _colPins, _ROWS, _COLS);
    }
    return singleton_instance;
}

void Keypad_4x3::onLED() {
    gpio_pin_set_dt(&led_key_pad, 0);
}

void Keypad_4x3::offLED() {
    gpio_pin_set_dt(&led_key_pad, 1);
}

void Keypad_4x3::subscribe(std::function<void(const KeyState, const char)> callback) {
    _callbacks.push_back(callback);
}