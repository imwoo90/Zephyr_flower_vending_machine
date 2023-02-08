#pragma once

#include <MachineState.h>
#include <MachineData.h>

class InputMoney : public MachineState {
private:
    uint32_t _inputMoney;
    uint32_t _column;
    k_timer _timer;
    InputMoney();
    virtual void initialize();
public:
    static InputMoney* getInstance(int column);
    virtual MachineState* pressKey(const char key);
    virtual MachineState* recognizeBanknote(const int banknote);
    virtual MachineState* timeout(const int signal);
};
