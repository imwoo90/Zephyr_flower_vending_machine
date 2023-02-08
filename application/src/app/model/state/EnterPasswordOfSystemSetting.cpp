#include "EnterPasswordOfSystemSetting.h"

#include "SystemSetting.h"
#include "Selling.h"
#include "StopSelling.h"
bool EnterPasswordOfSystemSetting::isMatched(uint32_t password) {
    return _database->getPasswordOfSystemSetting() == password;
}

MachineState* EnterPasswordOfSystemSetting::decide(uint32_t password) {
    if (_isChangePasswords) {
        _database->setPasswordOfSystemSetting(password);
        // _database->flush(TypeStaticData);
        return this;
    }
    return SystemSetting::getInstance();
}

MachineState* EnterPasswordOfSystemSetting::cancel() {
    if (_isChangePasswords) {
        return PasswordChange::getInstance();
    } else if (StopSelling::isStop()) {
        return StopSelling::getInstance();
    }
    return Selling::getInstance();
}

void EnterPasswordOfSystemSetting::initialize() {
    // init data
    _data.clear();
    _data["state"] = "EnterPasswordOfSystemSetting";
    if (_isChangePasswords) {
        char buf[32];
        sprintf(buf, "%04d", _database->getPasswordOfSystemSetting());
        _data["param_0"] = buf;
    } else {
        _data["param_0"] = "0000";
    }
}

EnterPasswordOfSystemSetting* EnterPasswordOfSystemSetting::getInstance(bool changePassword) {
    static EnterPasswordOfSystemSetting singleton_instance;
    singleton_instance._isChangePasswords = changePassword;
    singleton_instance.initialize();
    return &singleton_instance;
}
