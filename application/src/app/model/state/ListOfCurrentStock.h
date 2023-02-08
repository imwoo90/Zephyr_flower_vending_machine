#pragma once

#include <MachineState.h>
#include <MachineData.h>

class ListOfCurrentStock : public MachineState {
private:
    uint32_t _page;

    ListOfCurrentStock();
    virtual void initialize();

    void loadListOfCurrentStock();
public:
    static ListOfCurrentStock* getInstance();

    virtual MachineState* pressKey(const char key);
};
