#pragma once

#include <MachineState.h>
#include <MachineData.h>
#include "PasswordChange.h"
class EnterPassword : public MachineState {
private:
    virtual bool isMatched(uint32_t password) = 0;
    virtual MachineState* decide(uint32_t password) = 0;
    virtual MachineState* cancel() = 0;
public:
    bool _isChangePasswords;
    virtual MachineState* pressKey(const char key);
};

