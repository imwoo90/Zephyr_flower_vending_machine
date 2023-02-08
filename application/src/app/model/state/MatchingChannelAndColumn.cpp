#include "MatchingChannelAndColumn.h"

#include "VendingMachineModeSetting.h"

void MatchingChannelAndColumn::initialize() {
    // init data
    _data.clear();
    _data["state"] = "MatchingChannelAndColumn";
    _data["param_0"] = "000"; // 001 column
    _data["param_1"] = "000";
    _selection = 0;
    _data["selection"] = "param_0";
}

MatchingChannelAndColumn* MatchingChannelAndColumn::getInstance() {
    static MatchingChannelAndColumn singleton_instance;
    singleton_instance.initialize();
    return &singleton_instance;
}

MachineState* MatchingChannelAndColumn::pressKey(const char key) {
    static uint32_t column, channel;
    MachineState* next = this;
    switch ( key ) {
    case '*':
        next = VendingMachineModeSetting::getInstance();
        break;
    case '#':
        if (_selection == 0) {
            column = std::stoi(_data["param_0"])-1;
            if( !(0 <= column && column < _database->getNumberOfColumns()) ) {
                break;
            }

            _selection = 1;
            _data["selection"] = "param_1";
        } else {
            channel = std::stoi(_data["param_1"])-1;

            if( !(0 <= channel && channel < _database->getNumberOfColumns()) ){
                break;
            }

            _selection = 0;
            _data["selection"] = "param_0";
            _database->setChannel(column, channel);
            // _database->flush(TypeColumnData);
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
