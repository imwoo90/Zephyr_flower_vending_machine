#pragma once

#include <MachineState.h>
#include <MachineData.h>

class ColumnTestManul : public MachineState {
private:
    ColumnTestManul() {}
    virtual void initialize();
public:
    static ColumnTestManul* getInstance();

    virtual MachineState* releaseKey(const char key);
    virtual MachineState* pressKey(const char key);
};
