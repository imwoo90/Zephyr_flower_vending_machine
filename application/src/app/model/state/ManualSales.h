#pragma once

#include <MachineState.h>
#include <MachineData.h>

class ManualSales : public MachineState {
private:
    uint32_t _column, _is_running;

    ManualSales() {}
    virtual void initialize();
public:
    static ManualSales* getInstance();

    virtual MachineState* systemMessage(const SystemMessage mgs);
    virtual MachineState* pressKey(const char key);
};
