#pragma once

#include <MachineState.h>
#include <MachineData.h>

class SystemSetting : public MachineState {
private:
    SystemSetting() {}
    virtual void initialize();
public:
    static SystemSetting* getInstance();

    virtual MachineState* pressKey(const char key);
};
