#pragma once

#include <MachineState.h>
#include <MachineData.h>

class MainManagement : public MachineState {
private:
    MainManagement() {}
    virtual void initialize();
public:
    static MainManagement* getInstance();

    virtual MachineState* pressKey(const char key);
};
