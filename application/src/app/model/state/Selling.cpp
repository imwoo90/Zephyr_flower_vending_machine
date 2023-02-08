#include "Selling.h"

#include "EnterProductNumber.h"

void Selling::initialize() {
    // init data
    _data.clear();
    _data["state"] = "Selling";
    _data["BanknoteReader"] = "disable";
}

Selling* Selling::getInstance() {
    static Selling singleton_instance;
    singleton_instance.initialize();
    return &singleton_instance;
}

MachineState* Selling::pressKey(const char key) {
    return EnterProductNumber::getInstance();
}
