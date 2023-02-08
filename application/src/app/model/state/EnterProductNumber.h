#pragma once

#include <MachineState.h>
#include <MachineData.h>

class EnterProductNumber : public MachineState {
private:
    k_timer _timer;
    EnterProductNumber();
    virtual void initialize();
public:
    static EnterProductNumber* getInstance();
    virtual MachineState* pressKey(const char key);
    virtual MachineState* timeout(const int signal);
};
