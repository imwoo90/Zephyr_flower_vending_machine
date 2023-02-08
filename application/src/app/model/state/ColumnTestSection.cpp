#include "ColumnTestSection.h"

#include "WorkingTest.h"

void ColumnTestSection::initialize() {
    // init data
    _data.clear();
    _data["state"] = "ColumnTestSection";
    _data["param_0"] = "000";
    _data["param_1"] = "000";
    _selection = 0;
    _data["selection"] = "param_0";
}

ColumnTestSection* ColumnTestSection::getInstance() {
    static ColumnTestSection singleton_instance;
    singleton_instance.initialize();
    return &singleton_instance;
}

MachineState* ColumnTestSection::systemMessage(const SystemMessage mgs) {
    uint32_t column_e;
    char buf[32];
    switch (mgs) {
    case DelayCall: // loop column_s ~ column_e
        if (_running_test == false)
            break;

        column_e = std::stoi(_data["param_1"]) - 1;
        _data["LockerType"] = itoa(_database->getMotorType(_column), buf, 10);
        _data["LockerChannel"] = itoa(_database->getChannel(_column), buf, 10);
        if (_column < column_e) {
            _data["sysMsg"] = "DelayCall";
            if (_data["LockerType"] == "1") {
                _data["sysMsgArg_0"] = "1000"; // Delay 1000ms for DelayCall systemMessage
            } else if (_data["LockerType"] == "2") {
                _data["sysMsgArg_0"] = "8000"; // Delay 8000ms for DelayCall systemMessage
            }
        } else {
            _running_test = false;
        }
        _column += 1;
        break;
    }
    return this;
}

MachineState* ColumnTestSection::pressKey(const char key) {
    uint32_t column_s, column_e;
    MachineState* next = this;

    _data["LockerType"] = "";
    _data["LockerChannel"] = "";
    _data["sysMsg"] = "";
    _data["sysMsgArg_0"] = "";

    switch ( key ) {
    case '#':
        if (_running_test == true)
            break;

        if (_selection == 0) {
            column_s = std::stoi(_data["param_0"]) - 1;
            if (!(0 <= column_s && column_s < _database->getNumberOfColumns())) {
                break;
            }
            _selection = 1;
            _data["selection"] = "param_1";
        } else if (_selection == 1) {
            column_e = std::stoi(_data["param_1"]) - 1;
            if (!(0 <= column_e && column_e < _database->getNumberOfColumns())) {
                break;
            }
            _selection = 0;
            _data["selection"] = "param_0";
            _data["sysMsg"] = "DelayCall";
            _data["sysMsgArg_0"] = "1000"; // Delay 1000ms for DelayCall systemMessage
            _column = std::stoi(_data["param_0"]) - 1;
            _running_test = true;
        }
        break;
    case '*':
        _running_test = false;
        next = WorkingTest::getInstance();
        break;
    default: {//1~9
        if (_running_test == true)
            break;

        char param[] = "param_0";
        param[6] = '0' + _selection;
        std::string &param_0 = _data[param];
        rotate(param_0.begin(), param_0.begin()+1, param_0.end());
        param_0[param_0.length()-1] = key;
        _data["selection"] = param;
        break;}
    }
    return next;
}
