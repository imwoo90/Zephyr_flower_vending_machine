#pragma once

#include <MachineState.h>
#include <MachineData.h>

class ManualSales : public MachineState {
private:
    uint32_t _column;

    ManualSales() {}
    virtual void initialize();
public:
    static ManualSales* getInstance();

    virtual MachineState* releaseKey(const char key);
    virtual MachineState* pressKey(const char key);
};
