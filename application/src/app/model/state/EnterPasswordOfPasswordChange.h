#pragma once

#include "EnterPassword.h"


class EnterPasswordOfPasswordChange : public EnterPassword {
private:
    EnterPasswordOfPasswordChange() {}
    virtual bool isMatched(uint32_t password);
    virtual MachineState* decide(uint32_t password);
    virtual MachineState* cancel();
    virtual void initialize();
public:
    static EnterPasswordOfPasswordChange* getInstance(bool changePassword = false);
};
