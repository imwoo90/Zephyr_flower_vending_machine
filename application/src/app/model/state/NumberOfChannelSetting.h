#pragma once

#include <MachineState.h>
#include <MachineData.h>

class NumberOfChannelSetting : public MachineState {
private:
    int _selection;
    NumberOfChannelSetting() {}
    virtual void initialize();
public:
    static NumberOfChannelSetting* getInstance();

    virtual MachineState* pressKey(const char key);
};
