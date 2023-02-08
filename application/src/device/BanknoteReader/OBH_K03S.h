#pragma once

#include <Arduino.h>
#include "BanknoteReader.h"

typedef enum {
    RESET_WAIT,
    WAIT,
    STARTWAIT,
    RECOGNITION_RETURN,
    RECOGNITION_WAIT,
    RECOGNITION_END,
    RETURN_START,
    RETURN_WAIT,
    RETURN_END,
    STACK_START,
    STACK_WAIT,
    STACK_END,
    ERROR_WAIT,
    INSERT_ENABLE,
    INSERT_DISABLE,
    STACK_OPENED = 0X10,
    FORCESTACK_WAIT,
    FORCESTACK_END,
} ActiveStatus;

class OBH_K03S : public BanknoteReader {
private:
    Stream* _serial = NULL;

    int process(char _buf[5]);
    int activeStatusProcess(ActiveStatus reg);
    bool receiveCommnad(const char* _buf, const char* cmd);
    void sendCommand(const char*);
    virtual int getBillData();

    OBH_K03S() {};
public:
    static OBH_K03S* getInstance(Stream &serial);
    virtual int initialized();
    virtual void enable();
    virtual void disable();
};
