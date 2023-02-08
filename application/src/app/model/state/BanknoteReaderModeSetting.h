#pragma once

#include <MachineState.h>
#include <MachineData.h>

class BanknoteReaderModeSetting : public MachineState {
private:
    BanknoteReaderModeSetting() {}
    virtual void initialize();
public:
    static BanknoteReaderModeSetting* getInstance();

    virtual MachineState* pressKey(const char key);
};
