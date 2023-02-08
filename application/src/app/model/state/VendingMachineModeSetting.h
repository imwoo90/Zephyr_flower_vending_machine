#pragma once

#include <MachineState.h>
#include <MachineData.h>

class VendingMachineModeSetting : public MachineState {
private:
    VendingMachineModeSetting() {}
    virtual void initialize();
public:
    static VendingMachineModeSetting* getInstance();

    virtual MachineState* pressKey(const char key);
};
