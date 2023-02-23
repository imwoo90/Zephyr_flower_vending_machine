#pragma once

#include <MachineState.h>
#include <MachineData.h>

class AdditionalStock : public MachineState {
private:
    int _selection;
    AdditionalStock() {}
    virtual void initialize();
public:
    static AdditionalStock* getInstance();

    virtual MachineState* releaseKey(const char key);
    virtual MachineState* pressKey(const char key);
};
