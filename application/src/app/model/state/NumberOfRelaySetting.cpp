#include "NumberOfRelaySetting.h"

#include "VendingMachineModeSetting.h"

void NumberOfRelaySetting::initialize() {
    char mode[5];
    // init data
    _data.clear();
    _data["state"] = "NumberOfRelaySetting";
    sprintf(mode, "%02d", _database->getNumberOfRelays());
    _data["param_0"] = mode;
}

NumberOfRelaySetting* NumberOfRelaySetting::getInstance() {
    static NumberOfRelaySetting singleton_instance;
    singleton_instance.initialize();
    return &singleton_instance;
}

MachineState* NumberOfRelaySetting::pressKey(const char key) {
    int numOfRelay;
    MachineState* next = this;

    _data["deinitRelays"] = "";

    switch ( key ) {
    case '*':
        next = VendingMachineModeSetting::getInstance();
        break;
    case '#':
        numOfRelay = std::stoi(_data["param_0"]);
        if ( 0 < numOfRelay && numOfRelay <= 12) {
            _database->setNumberOfRelay(numOfRelay);
            _data["deinitRelays"] = "Running";
        }
        // _database->flush(TypeAll);
        break;
    default:{
        std::string &param_0 = _data["param_0"];
        rotate(param_0.begin(), param_0.begin()+1, param_0.end());
        param_0[param_0.length()-1] = key;
        break;}
    }
    return next;
}
