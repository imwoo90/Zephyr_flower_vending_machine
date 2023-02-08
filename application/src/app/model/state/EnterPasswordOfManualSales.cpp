#include "EnterPasswordOfManualSales.h"

#include "SystemSetting.h"
#include "ManualSales.h"

bool EnterPasswordOfManualSales::isMatched(uint32_t password) {
    return _database->getPasswordOfManualSales() == password;
}

MachineState* EnterPasswordOfManualSales::decide(uint32_t password) {
    if (_isChangePasswords) {
        _database->setPasswordOfManualSales(password);
        // _database->flush(TypeStaticData);
        return this;
    }
    return ManualSales::getInstance();
}

MachineState* EnterPasswordOfManualSales::cancel() {
    if (_isChangePasswords) {
        return PasswordChange::getInstance();
    }
    return SystemSetting::getInstance();;
}

void EnterPasswordOfManualSales::initialize() {
    // init data
    _data.clear();
    _data["state"] = "EnterPasswordOfManualSales";
    if (_isChangePasswords) {
        char buf[32];
        sprintf(buf, "%06d", _database->getPasswordOfManualSales());
        _data["param_0"] = buf;
    } else {
        _data["param_0"] = "000000";
    }
}

EnterPasswordOfManualSales* EnterPasswordOfManualSales::getInstance(bool changePassword) {
    static EnterPasswordOfManualSales singleton_instance;
    singleton_instance._isChangePasswords = changePassword;
    singleton_instance.initialize();
    return &singleton_instance;
}

