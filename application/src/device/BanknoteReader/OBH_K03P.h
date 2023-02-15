#pragma once

#include "BanknoteReader.h"



class OBH_K03P : public BanknoteReader {
private:
    int _inhibitPin;
    int _vendPin;
    int _errorPin;

    OBH_K03P() {};
public:
    k_timer _timer;
    int _tmp_cntPulse;
    int _cntPulse;

    OBH_K03P* setPins(int inhibitPin, int vendPin, int errorPin);
    static OBH_K03P* getInstance();
    virtual int initialized();
    virtual void enable();
    virtual void disable();
    virtual int getBillData();
};
