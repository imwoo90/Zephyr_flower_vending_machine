#include "ColumnTestManul.h"

#include "WorkingTest.h"

void ColumnTestManul::initialize() {
    // init data
    _data.clear();
    _data["state"] = "ColumnTestManul";
    _data["param_0"] = "000";
}

ColumnTestManul* ColumnTestManul::getInstance() {
    static ColumnTestManul singleton_instance;
    singleton_instance.initialize();
    return &singleton_instance;
}

MachineState* ColumnTestManul::releaseKey(const char key) {
    _data["LockerType"] = "";
    _data["LockerChannel"] = "";
    return this;
}

MachineState* ColumnTestManul::pressKey(const char key) {
    MachineState* next = this;

    switch ( key ) {
    case '#':{
        static unsigned long startTime = 0;
        char buf[32];
        uint32_t column = std::stoi(_data["param_0"]) - 1;
        if (0 <= column && column < _database->getNumberOfColumns()) {
            std::string locker = itoa(_database->getMotorType(column), buf, 10);
            if (locker == "1" && (k_uptime_get_32() - startTime) < 1000) {
                break;
            } else if (locker == "2" && (k_uptime_get_32() - startTime) < 8000) {
                break;
            }
            startTime = k_uptime_get_32();
            _data["LockerType"] = locker;
            _data["LockerChannel"] = itoa(_database->getChannel(column), buf, 10);
        }
        break;}
    case '*':
        next = WorkingTest::getInstance();
        break;
    default: {//1~9
        std::string &param_1 = _data["param_0"];
        rotate(param_1.begin(), param_1.begin()+1, param_1.end());
        param_1[param_1.length()-1] = key;
        break;}
    }
    return next;
}
