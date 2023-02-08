#include "SalesInfo.h"

#include "MainManagement.h"

static void deleteSalesInfoCallBack( k_timer *xTimer ) {
    MachineState::_timeoutCallback(TimeoutDeleteSalesInfo);
}

SalesInfo::SalesInfo() {
    // _timer = xTimerCreate(
    //      /* Just a text name, not used by the RTOS
    //     kernel. */
    //     "SalesInfo",
    //     /* The timer period in ticks, must be
    //     greater than 0. */
    //     pdMS_TO_TICKS(5*1000),
    //     /* The timers will auto-reload themselves
    //     when they expire. */
    //     pdFALSE,
    //     /* The ID is used to store a count of the
    //     number of times the timer has expired, which
    //     is initialised to 0. */
    //     ( void * ) 0,
    //     /* Each timer calls the same callback when
    //     it expires. */
    //     deleteSalesInfoCallBack
    // );
    k_timer_init(&_timer, deleteSalesInfoCallBack, NULL);
}

void SalesInfo::initialize() {
    char buf[32];
    // init data
    _data.clear();
    _data["state"] = "SalesInfo";
    _data["param_0"] = itoa(_database->getNumberOfTotalSales(), buf, 10);
    _data["param_1"] = itoa(_database->getMoneyOfTotalSales(), buf, 10);
    _data["param_2"] = itoa(_database->getNumberOfManualSales(), buf, 10);
    _data["param_3"] = itoa(_database->getMoneyOfManualSales(), buf, 10);
}

SalesInfo* SalesInfo::getInstance() {
    static SalesInfo singleton_instance;
    singleton_instance.initialize();
    return &singleton_instance;
}

MachineState* SalesInfo::timeout(const int signal) {
    _database->setNumberOfTotalSales(0);
    _database->setMoneyOfTotalSales(0);
    _database->setNumberOfManualSales(0);
    _database->setMoneyOfManualSales(0);
    // _database->flush(TypeStaticData);
    _data["param_0"] = "0";
    _data["param_1"] = "0";
    _data["param_2"] = "0";
    _data["param_3"] = "0";

    return this;
}

MachineState* SalesInfo::releaseKey(const char key) {
    MachineState* next = this;

    switch ( key ) {
    case '#':
        _isDisablePresskey = false;
        // if ( xTimerIsTimerActive(_timer) == pdFALSE )
        //     break;
        // xTimerStop(_timer, 0);
        if (k_timer_status_get(&_timer) > 0) {
            break;
        }
        k_timer_stop(&_timer);
        break;
    }
    return next;
}

MachineState* SalesInfo::pressKey(const char key) {
    MachineState* next = this;
    if (_isDisablePresskey)
        return next;

    switch ( key ) {
    case '*':
        next = MainManagement::getInstance();
        break;
    case '#':
        _isDisablePresskey = true;
        // xTimerStart(_timer, 0);
        k_timer_start(&_timer, K_MSEC(5*1000), K_NO_WAIT);
        break;
    }
    return next;
}
