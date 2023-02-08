#pragma once

#include <MachineState.h>
#include <MachineData.h>

class WorkingTest : public MachineState {
private:
    WorkingTest() {}
    virtual void initialize();
public:
    static WorkingTest* getInstance();

    virtual MachineState* pressKey(const char key);
};
