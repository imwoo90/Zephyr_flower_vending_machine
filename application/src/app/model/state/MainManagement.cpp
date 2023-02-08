#include "MainManagement.h"

#include "SystemSetting.h"
#include "SalesInfo.h"
#include "SetGoods.h"
#include "WorkingTest.h"
#include "ListOfCurrentStock.h"
#include "ListOfAdditionalStock.h"

void MainManagement::initialize() {
    // init data
    _data.clear();
    _data["state"] = "MainManagement";
}

MainManagement* MainManagement::getInstance() {
    static MainManagement singleton_instance;
    singleton_instance.initialize();
    return &singleton_instance;
}

MachineState* MainManagement::pressKey(const char key) {
    MachineState* next = this;
    switch ( key ) {
    case '*':
        next = SystemSetting::getInstance();
        break;
    case '1':
        next = SalesInfo::getInstance();
        break;
    case '2':
        next = SetGoods::getInstance();
        break;
    case '3':
        next = WorkingTest::getInstance();
        break;
    case '4':
         next = ListOfCurrentStock::getInstance();
        break;
    case '5':
         next = ListOfAdditionalStock::getInstance();
        break;
    }
    return next;
}
