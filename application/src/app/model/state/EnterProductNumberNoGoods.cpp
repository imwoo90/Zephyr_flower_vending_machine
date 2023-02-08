#include "EnterProductNumberNoGoods.h"

#include "EnterProductNumber.h"

static void viewTimeoutCallBack( k_timer *xTimer ) {
    MachineState::_timeoutCallback(TimeoutEnterProductNumberNoGoods);
}

EnterProductNumberNoGoods::EnterProductNumberNoGoods() {
    // _timer = xTimerCreate(
    //      /* Just a text name, not used by the RTOS
    //     kernel. */
    //     "EnterProductNumberNoGoods",
    //     /* The timer period in ticks, must be
    //     greater than 0. */
    //     pdMS_TO_TICKS(2*1000),
    //     /* The timers will auto-reload themselves
    //     when they expire. */
    //     pdFALSE,
    //     /* The ID is used to store a count of the
    //     number of times the timer has expired, which
    //     is initialised to 0. */
    //     ( void * ) 0,
    //     /* Each timer calls the same callback when
    //     it expires. */
    //     viewTimeoutCallBack
    // );
    k_timer_init(&_timer, viewTimeoutCallBack, NULL);
}

void EnterProductNumberNoGoods::initialize() {
    // init data
    _data.clear();
    _data["state"] = "EnterProductNumberNoGoods";

    //view timeout start
    // xTimerStart(_timer, 0);
    k_timer_start(&_timer, K_MSEC(2*1000), K_NO_WAIT);
}

EnterProductNumberNoGoods* EnterProductNumberNoGoods::getInstance() {
    static EnterProductNumberNoGoods singleton_instance;
    singleton_instance.initialize();
    return &singleton_instance;
}

MachineState* EnterProductNumberNoGoods::timeout(const int signal) {
    return EnterProductNumber::getInstance();
}
