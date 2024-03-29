#pragma once

#include "EnterPassword.h"

class EnterPasswordOfVendingMachineModeSetting : public EnterPassword {
private:
    EnterPasswordOfVendingMachineModeSetting() {}
    virtual bool isMatched(uint32_t password);
    virtual MachineState* decide(uint32_t password);
    virtual MachineState* cancel();
    virtual void initialize();
public:
    static EnterPasswordOfVendingMachineModeSetting* getInstance(bool changePassword = false);
};
