#include "SystemSetting.h"

#include "Selling.h"
#include "StopSelling.h"
#include "EnterPasswordOfVendingMachineModeSetting.h"
#include "EnterPasswordOfMainManagement.h"
#include "EnterPasswordOfAdditionalStock.h"
#include "EnterPasswordOfManualSales.h"

void SystemSetting::initialize() {
    // init data
    _data.clear();
    _data["state"] = "SystemSetting";
}

SystemSetting* SystemSetting::getInstance() {
    static SystemSetting singleton_instance;
    singleton_instance.initialize();
    return &singleton_instance;
}

MachineState* SystemSetting::pressKey(const char key) {
    MachineState* next = this;
    switch ( key ) {
    case '*':
        _database->flush(TypeAll);
        if (StopSelling::isStop()) {
            return StopSelling::getInstance();
        } else {
            next = Selling::getInstance();
        }
        break;
    case '1':
        next = EnterPasswordOfVendingMachineModeSetting::getInstance();
        break;
    case '2':
        next = EnterPasswordOfMainManagement::getInstance();
        break;
    case '3':
        next = EnterPasswordOfAdditionalStock::getInstance();
        break;
    case '4':
        next = EnterPasswordOfManualSales::getInstance();
        break;
    }
    return next;
}
