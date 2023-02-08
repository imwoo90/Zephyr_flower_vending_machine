#include "StopSelling.h"

#include "EnterPasswordOfSystemSetting.h"

bool StopSelling::_isStop;

void StopSelling::initialize() {
    // init data
    _data.clear();
    _data["state"] = "StopSelling";
    _isStop = true;
}

StopSelling* StopSelling::getInstance() {
    static StopSelling singleton_instance;
    singleton_instance.initialize();
    return &singleton_instance;
}

MachineState* StopSelling::pressKey(const char key) {
    return EnterPasswordOfSystemSetting::getInstance();
}
