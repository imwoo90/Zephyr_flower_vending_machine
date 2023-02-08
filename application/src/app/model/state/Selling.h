#pragma once

#include <MachineState.h>
#include <MachineData.h>

class Selling : public MachineState {
private:
    Selling() {}
    virtual void initialize();
public:
    static Selling* getInstance();

    virtual MachineState* pressKey(const char key);
};
