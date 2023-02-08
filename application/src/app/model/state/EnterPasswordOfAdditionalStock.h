#pragma once

#include "EnterPassword.h"


class EnterPasswordOfAdditionalStock : public EnterPassword {
private:
    EnterPasswordOfAdditionalStock() {}
    virtual bool isMatched(uint32_t password);
    virtual MachineState* decide(uint32_t password);
    virtual MachineState* cancel();
    virtual void initialize();
public:
    static EnterPasswordOfAdditionalStock* getInstance(bool changePassword = false);
};
