#include "ManualSales.h"

#include "SystemSetting.h"

void ManualSales::initialize() {
    // init data
    _data.clear();
    _data["state"] = "ManualSales";
    _data["param_0"] = "000";
    _data["param_1"] = "000000";
}

ManualSales* ManualSales::getInstance() {
    static ManualSales singleton_instance;
    singleton_instance.initialize();
    return &singleton_instance;
}

MachineState* ManualSales::systemMessage(const SystemMessage mgs) {
    char buf[32];
    switch (mgs) {
    case DelayCall:
        if (_is_running == false)
            break;

        _database->setNumberOfManualSales(1 + _database->getNumberOfManualSales());
        _database->setMoneyOfManualSales(std::stoi(_data["param_1"]) + _database->getMoneyOfManualSales());
        // _database->flush(TypeStaticData);
        _data["LockerType"] = itoa(_database->getMotorType(_column), buf, 10);
        _data["LockerChannel"] = itoa(_database->getChannel(_column), buf, 10);
        _is_running = false;
        break;
    }
    return this;
}

MachineState* ManualSales::pressKey(const char key) {
    MachineState* next = this;
    char buf[32];

    _data["LockerType"] = "";
    _data["LockerChannel"] = "";
    _data["sysMsg"] = "";
    _data["sysMsgArg_0"] = "";

    switch ( key ) {
    case '*':
        _is_running = false;
        next = SystemSetting::getInstance();
        break;
    case '#':
        if (_is_running == true)
            break;
        _column = std::stoi(_data["param_0"]) - 1;
        if (0<= _column && _column < _database->getNumberOfColumns() ) {
            uint32_t price = _database->getPrice(_column);
            if (price <= 0)
                break;

            _data["param_1"] = itoa(price, buf, 10);
            _data["sysMsg"] = "DelayCall";
            _data["sysMsgArg_0"] = "1000"; // Delay 1000ms for DelayCall systemMessage
            _is_running = true;
        }
        break;
    default: {//1~9
        if (_is_running == true)
            break;
        std::string &param_0 = _data["param_0"];
        rotate(param_0.begin(), param_0.begin()+1, param_0.end());
        param_0[param_0.length()-1] = key;
        break;}
    }
    return next;
}
