#pragma once

#include <MachineState.h>
#include <MachineData.h>

class PasswordChange : public MachineState {
private:
    PasswordChange() {}
    virtual void initialize();
public:
    static PasswordChange* getInstance();

    virtual MachineState* pressKey(const char key);
};
