#pragma once

#include <MachineState.h>
#include <MachineData.h>

class NumberOfRelaySetting : public MachineState {
private:
    NumberOfRelaySetting() {}
    virtual void initialize();
public:
    static NumberOfRelaySetting* getInstance();

    virtual MachineState* pressKey(const char key);
};
