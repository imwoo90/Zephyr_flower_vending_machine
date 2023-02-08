#pragma once

#include <MachineState.h>
#include <MachineData.h>

class MatchingChannelAndColumn : public MachineState {
private:
    int _selection;
    MatchingChannelAndColumn() {}
    virtual void initialize();
public:
    static MatchingChannelAndColumn* getInstance();

    virtual MachineState* pressKey(const char key);
};
