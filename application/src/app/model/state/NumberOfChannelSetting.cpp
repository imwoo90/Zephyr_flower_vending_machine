#include "NumberOfChannelSetting.h"

#include "VendingMachineModeSetting.h"

void NumberOfChannelSetting::initialize() {
    // init data
    _data.clear();
    _data["state"] = "NumberOfChannelSetting";
    _data["param_0"] = "00";
    _data["param_1"] = "00";
    _data["param_2"] = "00";
    _selection = 0;
    _data["selection"] = "param_0";
}

NumberOfChannelSetting* NumberOfChannelSetting::getInstance() {
    static NumberOfChannelSetting singleton_instance;
    singleton_instance.initialize();
    return &singleton_instance;
}

MachineState* NumberOfChannelSetting::pressKey(const char key) {
    MachineState* next = this;

    _data["deinitRelays"] = "";

    switch ( key ) {
    case '*':
        next = VendingMachineModeSetting::getInstance();
        break;
    case '#':
        if ( _selection == 0) {
            uint32_t start = std::stoi(_data["param_0"]);
            if ( !(0 < start && start <= _database->getNumberOfRelays()) )
                break;

            _selection = 1;
            _data["selection"] = "param_1";
        } else if ( _selection == 1) {
            uint32_t end = std::stoi(_data["param_1"]);
            if ( !(0 < end && end <= _database->getNumberOfRelays()) )
                break;
            _selection = 2;
            _data["selection"] = "param_2";
        } else if ( _selection == 2) {
            uint32_t start = std::stoi(_data["param_0"]);
            uint32_t end = std::stoi(_data["param_1"]);
            uint32_t numOfChannels = std::stoi(_data["param_2"]);

            for(uint32_t i = start; i <= end; i++) {
                // relay index is i-1 (started zero index)
                _database->setNumberOfChannels(i-1, numOfChannels);
            }
            // _database->flush(TypeAll);
            _selection = 0;
            _data["selection"] = "param_0";
            _data["deinitRelays"] = "Running";
        }
        break;
    default: {//1~9
        char param[] = "param_0";
        param[6] = '0' + _selection;
        std::string &param_0 = _data[param];
        rotate(param_0.begin(), param_0.begin()+1, param_0.end());
        param_0[param_0.length()-1] = key;
        _data["selection"] = param;
        break;}
    }
    return next;
}
