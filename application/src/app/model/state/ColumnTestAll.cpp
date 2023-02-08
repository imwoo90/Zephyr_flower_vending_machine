#include "ColumnTestAll.h"

#include "WorkingTest.h"

void ColumnTestAll::initialize() {
    // init data
    _data.clear();
    _data["state"] = "ColumnTestAll";
    _data["param_0"] = "000";
}

ColumnTestAll* ColumnTestAll::getInstance() {
    static ColumnTestAll singleton_instance;
    singleton_instance.initialize();
    return &singleton_instance;
}

MachineState* ColumnTestAll::systemMessage(const SystemMessage mgs) {
    int column_e;
    char buf[32];
    switch (mgs) {
    case DelayCall: // loop column_s ~ column_e
        if (_running_test == false)
            break;

        column_e = _database->getNumberOfColumns()-1;
        _data["LockerType"] = itoa(_database->getMotorType(_column), buf, 10);
        _data["LockerChannel"] = itoa(_database->getChannel(_column), buf, 10);
        if (_column < column_e) {
            _data["sysMsg"] = "DelayCall";
            if (_data["LockerType"] == "1") {
                _data["sysMsgArg_0"] = "1000"; // Delay 1000ms for DelayCall systemMessage
            } else if (_data["LockerType"] == "2") {
                _data["sysMsgArg_0"] = "8000"; // Delay 1000ms for DelayCall systemMessage
            }
        } else {
            _running_test = false;
        }
        _column += 1;
        break;
    }
    return this;
}

MachineState* ColumnTestAll::pressKey(const char key) {
    int column_s, column_e;
    MachineState* next = this;

    _data["LockerType"] = "";
    _data["LockerChannel"] = "";
    _data["sysMsg"] = "";
    _data["sysMsgArg_0"] = "";

    switch ( key ) {
    case '#':
        if (_running_test == true)
            break;

        column_s = std::stoi(_data["param_0"]) - 1;
        column_e = _database->getNumberOfColumns()-1;
        if (!(0 <= column_s && column_s <= column_e)) {
            break;
        }

        _data["sysMsg"] = "DelayCall";
        _data["sysMsgArg_0"] = "1000"; // Delay 1000ms for DelayCall systemMessage
        _column = column_s;
        _running_test = true;
        break;
    case '*':
        _running_test = false;
        next = WorkingTest::getInstance();
        break;
    default: {//1~9
        if (_running_test == true)
            break;

        std::string &param_1 = _data["param_0"];
        rotate(param_1.begin(), param_1.begin()+1, param_1.end());
        param_1[param_1.length()-1] = key;
        break;}
    }
    return next;
}
