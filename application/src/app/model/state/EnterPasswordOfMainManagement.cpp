#include "EnterPasswordOfMainManagement.h"

#include "SystemSetting.h"
#include "MainManagement.h"

bool EnterPasswordOfMainManagement::isMatched(uint32_t password) {
    return _database->getPasswordOfMainManagement() == password;
}

MachineState* EnterPasswordOfMainManagement::decide(uint32_t password) {
    if (_isChangePasswords) {
        _database->setPasswordOfMainManagement(password);
        // _database->flush(TypeStaticData);
        return this;
    }
    return MainManagement::getInstance();
}

MachineState* EnterPasswordOfMainManagement::cancel() {
    if (_isChangePasswords) {
        return PasswordChange::getInstance();
    }
    return SystemSetting::getInstance();
}

void EnterPasswordOfMainManagement::initialize() {
    // init data
    _data.clear();
    _data["state"] = "EnterPasswordOfMainManagement";
    if (_isChangePasswords) {
        char buf[32];
        sprintf(buf, "%06d", _database->getPasswordOfMainManagement());
        _data["param_0"] = buf;
    } else {
        _data["param_0"] = "000000";
    }
}

EnterPasswordOfMainManagement* EnterPasswordOfMainManagement::getInstance(bool changePassword) {
    static EnterPasswordOfMainManagement singleton_instance;
    singleton_instance._isChangePasswords = changePassword;
    singleton_instance.initialize();
    return &singleton_instance;
}
