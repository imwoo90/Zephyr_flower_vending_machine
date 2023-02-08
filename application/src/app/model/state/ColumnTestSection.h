#pragma once

#include <MachineState.h>
#include <MachineData.h>

class ColumnTestSection : public MachineState {
private:
    uint32_t _selection, _column, _running_test;

    ColumnTestSection() {}
    virtual void initialize();
public:
    static ColumnTestSection* getInstance();

    virtual MachineState* systemMessage(const SystemMessage mgs);
    virtual MachineState* pressKey(const char key);
};
