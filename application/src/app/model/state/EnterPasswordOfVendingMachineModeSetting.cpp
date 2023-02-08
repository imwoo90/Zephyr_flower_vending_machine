#include "EnterPasswordOfVendingMachineModeSetting.h"

#include "SystemSetting.h"
#include "VendingMachineModeSetting.h"


bool EnterPasswordOfVendingMachineModeSetting::isMatched(uint32_t password) {
    return _database->getPasswordOfVendingMachineModeSetting() == password;
}

MachineState* EnterPasswordOfVendingMachineModeSetting::decide(uint32_t password) {
    if (_isChangePasswords) {
        _database->setPasswordOfVendingMachineModeSetting(password);
        // _database->flush(TypeStaticData);
        return this;
    }
    return VendingMachineModeSetting::getInstance();
}

MachineState* EnterPasswordOfVendingMachineModeSetting::cancel() {
    if (_isChangePasswords) {
        return PasswordChange::getInstance();
    }
    return SystemSetting::getInstance();
}

void EnterPasswordOfVendingMachineModeSetting::initialize() {
    // init data
    _data.clear();
    _data["state"] = "EnterPasswordOfVendingMachineModeSetting";
    if (_isChangePasswords) {
        char buf[32];
        sprintf(buf, "%08d", _database->getPasswordOfVendingMachineModeSetting());
        _data["param_0"] = buf;
    } else {
        _data["param_0"] = "00000000";
    }
}

EnterPasswordOfVendingMachineModeSetting* EnterPasswordOfVendingMachineModeSetting::getInstance(bool changePassword) {
    static EnterPasswordOfVendingMachineModeSetting singleton_instance;
    singleton_instance._isChangePasswords = changePassword;
    singleton_instance.initialize();
    return &singleton_instance;
}
