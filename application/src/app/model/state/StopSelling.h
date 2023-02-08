#pragma once

#include <MachineState.h>
#include <MachineData.h>

class StopSelling : public MachineState {
private:
    static bool _isStop;

    StopSelling() {}
    virtual void initialize();
public:
    static StopSelling* getInstance();

    virtual MachineState* pressKey(const char key);


    static bool isStop() { return _isStop; }
};
