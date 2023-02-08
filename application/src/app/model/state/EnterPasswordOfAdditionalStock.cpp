#include "EnterPasswordOfAdditionalStock.h"
#include "SystemSetting.h"
#include "AdditionalStock.h"

bool EnterPasswordOfAdditionalStock::isMatched(uint32_t password) {
    return _database->getPasswordOfAdditionalStock() == password;
}

MachineState* EnterPasswordOfAdditionalStock::decide(uint32_t password) {
    if (_isChangePasswords) {
        _database->setPasswordOfAdditionalStock(password);
        // _database->flush(TypeStaticData);
        return this;
    }
    return AdditionalStock::getInstance();
}

MachineState* EnterPasswordOfAdditionalStock::cancel() {
    if (_isChangePasswords) {
        return PasswordChange::getInstance();
    }
    return SystemSetting::getInstance();;
}

void EnterPasswordOfAdditionalStock::initialize() {
    // init data
    _data.clear();
    _data["state"] = "EnterPasswordOfAdditionalStock";
    if (_isChangePasswords) {
        char buf[32];
        sprintf(buf, "%06d", _database->getPasswordOfAdditionalStock());
        _data["param_0"] = buf;
    } else {
        _data["param_0"] = "000000";
    }
}

EnterPasswordOfAdditionalStock* EnterPasswordOfAdditionalStock::getInstance(bool changePassword) {
    static EnterPasswordOfAdditionalStock singleton_instance;
    singleton_instance._isChangePasswords = changePassword;
    singleton_instance.initialize();
    return &singleton_instance;
}

