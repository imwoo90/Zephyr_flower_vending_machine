#pragma once

#include <MachineData.h>

#include <functional>
#include <unordered_map>
#include <string>
#include <vector>

typedef enum {
    TimeoutEnterProductNumber,
    TimeoutEnterProductNumberNoGoods,
    TimeoutInputMoney,
    TimeoutDeleteList,
    TimeoutDeleteSalesInfo,
} KindOfTimeout;

typedef enum {
    DelayCall,
} SystemMessage;

class MachineState {
private:
    virtual void initialize() = 0;
public:
    static std::function<void(const int)> _timeoutCallback;
    static std::function<void(std::unordered_map<std::string, std::string>)> _onChangedCallback;

    static std::unordered_map<std::string, std::string> _data;
    static MachineData* _database;

    virtual MachineState* systemMessage(const SystemMessage msg) { return this;}
    virtual MachineState* pressKey(const char key) { return this;}
    virtual MachineState* releaseKey(const char key) {return this;}
    virtual MachineState* recognizeBanknote(const int banknote) {return this;}
    virtual MachineState* timeout(const int signal) {return this;}
};

char *itoa(int num, char *str, int base);
