#pragma once

#include <MachineState.h>
#include <MachineData.h>

#include <functional>

class FlowVendingMachine {
private:
    MachineState* _state;
    FlowVendingMachine() {}
public:
    MachineData* _database;
    void initialize(std::function<void(std::unordered_map<std::string, std::string>)> onChangedCallback, std::function<void(const int)> timeoutCallback);
    void begin(bool isNormal);
    static FlowVendingMachine* getInstance() {
        static FlowVendingMachine singleton_instance;
        return &singleton_instance;
    }

    void pressKey(const char key);
    void releaseKey(const char key);
    void recognizeBanknote(const int bankNote);
    void systemMessage(const SystemMessage msg);
    void timeout(const int signal);
};
