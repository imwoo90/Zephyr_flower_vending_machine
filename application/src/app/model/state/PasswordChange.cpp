#include "PasswordChange.h"

#include "VendingMachineModeSetting.h"

#include "EnterPasswordOfSystemManagement.h"
#include "EnterPasswordOfSystemSetting.h"
#include "EnterPasswordOfVendingMachineModeSetting.h"
#include "EnterPasswordOfMainManagement.h"
#include "EnterPasswordOfAdditionalStock.h"
#include "EnterPasswordOfManualSales.h"
#include "EnterPasswordOfPasswordChange.h"

void PasswordChange::initialize() {
    char buf[32];
    auto _itoa = [](char* _buf, int n, int d) {
        char format[10] = "%00d";
        format[2] += n;
        sprintf(_buf, format, d);
        return _buf;
    };
    // init data
    _data.clear();
    _data["state"] = "PasswordChange";
    _data["param_0"] = _itoa(buf, 3,  _database->getPasswordOfSystemManagement());
    _data["param_1"] = _itoa(buf, 4, _database->getPasswordOfSystemSetting());
    _data["param_2"] = _itoa(buf, 8, _database->getPasswordOfVendingMachineModeSetting());
    _data["param_3"] = _itoa(buf, 6, _database->getPasswordOfMainManagement());
    _data["param_4"] = _itoa(buf, 6, _database->getPasswordOfAdditionalStock());
    _data["param_5"] = _itoa(buf, 6, _database->getPasswordOfManualSales());
    _data["param_6"] = _itoa(buf, 6, _database->getPasswordOfPasswordChange());
}

PasswordChange* PasswordChange::getInstance() {
    static PasswordChange singleton_instance;
    singleton_instance.initialize();
    return &singleton_instance;
}

MachineState* PasswordChange::pressKey(const char key) {
    const bool changePasword = true;
    MachineState* next = this;
    switch ( key ) {
    case '*':
        next = VendingMachineModeSetting::getInstance();
        break;
    case '1':
        next = EnterPasswordOfSystemManagement::getInstance(changePasword);
        break;
    case '2':
        next = EnterPasswordOfSystemSetting::getInstance(changePasword);
        break;
    case '3':
        next = EnterPasswordOfVendingMachineModeSetting::getInstance(changePasword);
        break;
    case '4':
        next = EnterPasswordOfMainManagement::getInstance(changePasword);
        break;
    case '5':
        next = EnterPasswordOfAdditionalStock::getInstance(changePasword);
        break;
    case '6':
        next = EnterPasswordOfManualSales::getInstance(changePasword);
        break;
    case '7':
        next = EnterPasswordOfPasswordChange::getInstance(changePasword);
        break;
    }
    return next;
}
