#include "EnterPasswordOfSystemManagement.h"
#include "SystemSetting.h"

bool EnterPasswordOfSystemManagement::isMatched(uint32_t password) {
    return _database->getPasswordOfSystemManagement() == password;
}

MachineState* EnterPasswordOfSystemManagement::decide(uint32_t password) {
    if (_isChangePasswords) {
        _database->setPasswordOfSystemManagement(password);
        // _database->flush(TypeStaticData);
        return this;
    }
    return this;
}

MachineState* EnterPasswordOfSystemManagement::cancel() {
    if (_isChangePasswords) {
        return PasswordChange::getInstance();
    }
    return SystemSetting::getInstance();
}

void EnterPasswordOfSystemManagement::initialize() {
    // init data
    _data.clear();
    _data["state"] = "EnterPasswordOfSystemManagement";
    if (_isChangePasswords) {
        char buf[32];
        sprintf(buf, "%03d", _database->getPasswordOfSystemManagement());
        _data["param_0"] = buf;
    } else {
        _data["param_0"] = "000";
    }
}

EnterPasswordOfSystemManagement* EnterPasswordOfSystemManagement::getInstance(bool changePassword) {
    static EnterPasswordOfSystemManagement singleton_instance;
    singleton_instance._isChangePasswords = changePassword;
    singleton_instance.initialize();
    return &singleton_instance;
}

