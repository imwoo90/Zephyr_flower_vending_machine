#pragma once

#include <MachineState.h>
#include <MachineData.h>

class ListOfAdditionalStock : public MachineState {
private:
    bool _isDisablePresskey;
    uint32_t _page;
    k_timer _timer;

    ListOfAdditionalStock();
    virtual void initialize();

    void loadListOfAdditionalStock();
public:
    static ListOfAdditionalStock* getInstance();

    virtual MachineState* timeout(const int signal);
    virtual MachineState* releaseKey(const char key);
    virtual MachineState* pressKey(const char key);
};
