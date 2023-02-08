#include "BanknoteReaderModeSetting.h"

#include "VendingMachineModeSetting.h"

void BanknoteReaderModeSetting::initialize() {
    char mode[5];
    // init data
    _data.clear();
    _data["state"] = "BanknoteReaderModeSetting";
    sprintf(mode, "%02d", _database->getBanknoteReaderMode());
    _data["param_0"] = mode;
}

BanknoteReaderModeSetting* BanknoteReaderModeSetting::getInstance() {
    static BanknoteReaderModeSetting singleton_instance;
    singleton_instance.initialize();
    return &singleton_instance;
}

MachineState* BanknoteReaderModeSetting::pressKey(const char key) {
    int mode;
    MachineState* next = this;
    switch ( key ) {
    case '*':
        next = VendingMachineModeSetting::getInstance();
        break;
    case '#':
        mode = std::stoi(_data["param_0"]);
        if ( 0 < mode && mode <= 2) {
            _database->setBanknoteReaderMode(mode);
            // _database->flush(TypeStaticData);
        }
        break;
    default:{
        std::string &param_0 = _data["param_0"];
        rotate(param_0.begin(), param_0.begin()+1, param_0.end());
        param_0[param_0.length()-1] = key;
        break;}
    }
    return next;
}
