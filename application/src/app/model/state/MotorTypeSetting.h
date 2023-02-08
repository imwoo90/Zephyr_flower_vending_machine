#pragma once

#include <MachineState.h>
#include <MachineData.h>

class MotorTypeSetting : public MachineState {
private:
    int _selection;
    MotorTypeSetting() {}
    virtual void initialize();
public:
    static MotorTypeSetting* getInstance();

    virtual MachineState* pressKey(const char key);
};
