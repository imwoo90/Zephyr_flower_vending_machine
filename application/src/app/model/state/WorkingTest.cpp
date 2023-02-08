#include "WorkingTest.h"

#include "MainManagement.h"
#include "ColumnTestManul.h"
#include "ColumnTestSection.h"
#include "ColumnTestAll.h"

void WorkingTest::initialize() {
    _data.clear();
    _data["state"] = "WorkingTest";
}

WorkingTest* WorkingTest::getInstance() {
    static WorkingTest singleton_instance;
    singleton_instance.initialize();
    return &singleton_instance;
}

MachineState* WorkingTest::pressKey(const char key) {
    MachineState* next = this;
    switch ( key ) {
    case '*':
        next = MainManagement::getInstance();
        break;
    case '1':
        next = ColumnTestManul::getInstance();
        break;
    case '2':
        next = ColumnTestSection::getInstance();
        break;
    case '3':
        next = ColumnTestAll::getInstance();
        break;
    }
    return next;
}
