#include "VendingMachineModeSetting.h"

#include "SystemSetting.h"

#include "BanknoteReaderModeSetting.h"
#include "NumberOfRelaySetting.h"
#include "NumberOfChannelSetting.h"
#include "MotorTypeSetting.h"
#include "MatchingChannelAndColumn.h"
#include "EnterPasswordOfPasswordChange.h"
#include "ListOfColumnData.h"

void VendingMachineModeSetting::initialize() {
    // init data
    _data.clear();
    _data["state"] = "VendingMachineModeSetting";
}

VendingMachineModeSetting* VendingMachineModeSetting::getInstance() {
    static VendingMachineModeSetting singleton_instance;
    singleton_instance.initialize();
    return &singleton_instance;
}

MachineState* VendingMachineModeSetting::pressKey(const char key) {
    MachineState* next = this;
    switch ( key ) {
    case '*':
        next = SystemSetting::getInstance();
        break;
    case '1':
        next = BanknoteReaderModeSetting::getInstance();
        break;
    case '2':
        next = NumberOfRelaySetting::getInstance();
        break;
    case '3':
        next = NumberOfChannelSetting::getInstance();
        break;
    case '4':
        next = MotorTypeSetting::getInstance();
        break;
    case '5':
        next = MatchingChannelAndColumn::getInstance();
        break;
    case '6':
        next = EnterPasswordOfPasswordChange::getInstance();
        break;
    case '7':
        next = ListOfColumnData::getInstance();
        break;
    }
    return next;
}
