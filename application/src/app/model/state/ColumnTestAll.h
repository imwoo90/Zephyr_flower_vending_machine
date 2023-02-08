#pragma once

#include <MachineState.h>
#include <MachineData.h>

class ColumnTestAll : public MachineState {
private:
    int _column, _running_test;

    ColumnTestAll() {}
    virtual void initialize();
public:
    static ColumnTestAll* getInstance();

    virtual MachineState* systemMessage(const SystemMessage mgs);
    virtual MachineState* pressKey(const char key);
};
