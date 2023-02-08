#pragma once

#include "EnterPassword.h"


class EnterPasswordOfSystemManagement : public EnterPassword {
private:
    EnterPasswordOfSystemManagement() {}
    virtual bool isMatched(uint32_t password);
    virtual MachineState* decide(uint32_t password);
    virtual MachineState* cancel();
    virtual void initialize();
public:
    static EnterPasswordOfSystemManagement* getInstance(bool changePassword = false);
};
