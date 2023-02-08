#pragma once

#include <Arduino.h>
#include "BanknoteReader.h"

#include <FreeRTOS.h>
#include <timers.h>

class OBH_K03P : public BanknoteReader {
private:
    int _inhibitPin;
    int _vendPin;
    int _errorPin;

    OBH_K03P() {};
public:
    QueueHandle_t _q;
    TimerHandle_t _timer;
    int _cntPulse;

    OBH_K03P* setPins(int inhibitPin, int vendPin, int errorPin);
    static OBH_K03P* getInstance();
    virtual int initialized();
    virtual void enable();
    virtual void disable();
    virtual int getBillData();
};
