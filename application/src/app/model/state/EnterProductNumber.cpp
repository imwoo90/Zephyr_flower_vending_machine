#include "EnterProductNumber.h"
#include "Selling.h"
#include "EnterPasswordOfSystemSetting.h"
#include "InputMoney.h"
#include "EnterProductNumberNoGoods.h"

static void keyTimeoutCallBack( k_timer *xTimer ) {
    MachineState::_timeoutCallback(TimeoutEnterProductNumber);
}

EnterProductNumber::EnterProductNumber() {
    // _timer = xTimerCreate(
    //      /* Just a text name, not used by the RTOS
    //     kernel. */
    //     "EnterProductNumber",
    //     /* The timer period in ticks, must be
    //     greater than 0. */
    //     pdMS_TO_TICKS(10*1000),
    //     /* The timers will auto-reload themselves
    //     when they expire. */
    //     pdFALSE,
    //     /* The ID is used to store a count of the
    //     number of times the timer has expired, which
    //     is initialised to 0. */
    //     ( void * ) 0,
    //     /* Each timer calls the same callback when
    //     it expires. */
    //     keyTimeoutCallBack
    // );
    k_timer_init(&_timer, keyTimeoutCallBack, NULL);
}

void EnterProductNumber::initialize() {
    // init data
    _data.clear();
    _data["state"] = "EnterProductNumber";
    _data["param_0"] = "000";

    //key timout start
    k_timer_start(&_timer, K_MSEC(10*1000), K_NO_WAIT);
}

EnterProductNumber* EnterProductNumber::getInstance() {
    static EnterProductNumber singleton_instance;
    singleton_instance.initialize();
    return &singleton_instance;
}

MachineState* EnterProductNumber::pressKey(const char key) {
    // if ( xTimerIsTimerActive(_timer) == pdFALSE )
    //     return this;
    if (k_timer_status_get(&_timer) > 0) {
        return this;
    }
    // xTimerStop(_timer, 0);
    k_timer_stop(&_timer);

    MachineState* next = this;
    switch ( key ) {
    case '#': {
        uint32_t n = std::stoi(_data["param_0"])-1;
        if ( n+1 == _database->getPasswordOfSystemManagement() ){
            next = EnterPasswordOfSystemSetting::getInstance();
        } else if ( 0 <= n && n < _database->getNumberOfColumns() ) {
            if (_database->getQuantity(n) > 0) {
                next =InputMoney::getInstance(n);
            } else {
                next = EnterProductNumberNoGoods::getInstance();
            }
        } else {
            next = EnterProductNumberNoGoods::getInstance();
        }
        break;}
    case '*': {
        next = Selling::getInstance();
        break;}
    default: {//1~9
        std::string &param_0 = _data["param_0"];
        rotate(param_0.begin(), param_0.begin()+1, param_0.end());
        param_0[param_0.length()-1] = key;
        k_timer_start(&_timer, K_MSEC(10*1000), K_NO_WAIT);
        break;}
    }
    return next;
}

MachineState* EnterProductNumber::timeout(const int signal) {
    return Selling::getInstance();
}
