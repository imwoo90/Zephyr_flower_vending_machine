#pragma once

#include <MachineState.h>
#include <MachineData.h>

class EnterProductNumberNoGoods : public MachineState {
private:
    k_timer _timer;
    EnterProductNumberNoGoods();
    virtual void initialize();
public:
    static EnterProductNumberNoGoods* getInstance();

    virtual MachineState* timeout(const int signal);
};
