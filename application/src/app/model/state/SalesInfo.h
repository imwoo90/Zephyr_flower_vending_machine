#pragma once

#include <MachineState.h>
#include <MachineData.h>

class SalesInfo : public MachineState {
private:
    bool _isDisablePresskey;
    int _page;
    k_timer _timer;

    SalesInfo();
    virtual void initialize();
public:
    static SalesInfo* getInstance();

    virtual MachineState* timeout(const int signal);
    virtual MachineState* pressKey(const char key);
    virtual MachineState* releaseKey(const char key);
};
