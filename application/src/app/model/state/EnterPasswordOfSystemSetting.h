#pragma once

#include "EnterPassword.h"

class EnterPasswordOfSystemSetting : public EnterPassword {
private:
    EnterPasswordOfSystemSetting() {}
    virtual bool isMatched(uint32_t password);
    virtual MachineState* decide(uint32_t password);
    virtual MachineState* cancel();
    virtual void initialize();
public:
    static EnterPasswordOfSystemSetting* getInstance(bool changePassword = false);
};

