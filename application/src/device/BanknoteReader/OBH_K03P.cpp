// 지폐 읽기가 안되는중 cntPulse 디버깅 해야함


#include "OBH_K03P.h"
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(obh_k03p);


static const struct device *gpio0 = DEVICE_DT_GET(DT_NODELABEL(gpio0));
static struct gpio_callback vendPinCallback;

static void cntPulse(const struct device *port,
                    struct gpio_callback *cb,
                    gpio_port_pins_t pins) {
    OBH_K03P* p = OBH_K03P::getInstance();
    static uint32_t falling_time = 0;

    if (falling_time == 0) {
        falling_time = k_uptime_get_32();
        return;
    } else {
        uint32_t pulse_time = k_uptime_get_32() - falling_time;
        falling_time = 0;
        if ( pulse_time < 99 || 101 < pulse_time) {
            return;
        }
    }

    if (k_timer_status_get(&p->_timer) == 0)
        k_timer_stop(&p->_timer);
    if (p->_tmp_cntPulse == 0)
        p->disable();
    p->_tmp_cntPulse += 1;
    k_timer_start(&p->_timer, K_MSEC(300), K_NO_WAIT);
}

static void billDataEndCallback(k_timer *timer)
{
    OBH_K03P* p = (OBH_K03P*)timer->user_data;
    switch(p->_tmp_cntPulse) {
    case 1:
    case 5:
    case 10:
        p->_cntPulse = p->_tmp_cntPulse;
        break;
    default:
        p->enable();
        break;
    }
    p->_tmp_cntPulse = 0;
}

// static void errorOccur(OBH_K03P* p) {

// }

void OBH_K03P::enable() {
    gpio_pin_set(gpio0, _inhibitPin, 1);
}

void OBH_K03P::disable() {
    gpio_pin_set(gpio0, _inhibitPin, 0);
}

int OBH_K03P::getBillData() {
    int billData = 0;
    if (_cntPulse) {
        billData = _cntPulse*1000;
        _cntPulse = 0;
    }
    return billData;
}

int OBH_K03P::initialized() {
    // pinMode(_inhibitPin, OUTPUT);
    gpio_pin_configure(gpio0, _inhibitPin, GPIO_OUTPUT);
    // pinMode(_vendPin, INPUT_PULLUP);
    gpio_pin_interrupt_configure(gpio0, _vendPin, GPIO_INPUT | GPIO_PULL_UP | GPIO_INT_EDGE_BOTH );
    // pinMode(_errorPin, INPUT_PULLUP);

    k_timer_init(&_timer, billDataEndCallback, NULL);
    _timer.user_data = this;

    gpio_init_callback(&vendPinCallback, cntPulse, BIT(_vendPin));
	gpio_add_callback(gpio0, &vendPinCallback);

    // attachInterrupt(_errorPin, errorOccur, FALLING, this);
    BanknoteReader::initialized();
    return 0;
}

OBH_K03P* OBH_K03P::setPins(int inhibitPin, int vendPin, int errorPin) {
    _inhibitPin = inhibitPin;
    _vendPin = vendPin;
    _errorPin = errorPin;
    _name = "OBH_K03P";
    return this;
}

OBH_K03P* OBH_K03P::getInstance() {
    static OBH_K03P singleton_instance;
    return &singleton_instance;
}
