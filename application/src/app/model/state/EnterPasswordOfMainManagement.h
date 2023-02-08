#pragma once

#include "EnterPassword.h"

class EnterPasswordOfMainManagement : public EnterPassword {
private:
    EnterPasswordOfMainManagement() {}
    virtual bool isMatched(uint32_t password);
    virtual MachineState* decide(uint32_t password);
    virtual MachineState* cancel();
    virtual void initialize();
public:
    static EnterPasswordOfMainManagement* getInstance(bool changePassword = false);
};

