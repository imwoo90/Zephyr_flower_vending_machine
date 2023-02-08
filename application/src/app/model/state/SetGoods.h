#pragma once

#include <MachineState.h>
#include <MachineData.h>

class SetGoods : public MachineState {
private:
    int _selection;
    SetGoods() {}
    virtual void initialize();
public:
    static SetGoods* getInstance();

    virtual MachineState* pressKey(const char key);
};
