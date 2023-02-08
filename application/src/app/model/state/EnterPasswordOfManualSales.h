#pragma once

#include "EnterPassword.h"

class EnterPasswordOfManualSales : public EnterPassword {
private:
    EnterPasswordOfManualSales() {}
    virtual bool isMatched(uint32_t password);
    virtual MachineState* decide(uint32_t password);
    virtual MachineState* cancel();
    virtual void initialize();
public:
    static EnterPasswordOfManualSales* getInstance(bool changePassword = false);
};
