#include "OBH_K03P.h"

static void cntPulse(OBH_K03P* p) {
    xTimerStopFromISR(p->_timer, 0);
    if (p->_cntPulse == 0)
        p->disable();
    p->_cntPulse += 1;
    xTimerStartFromISR(p->_timer, 0);
}
static void billDataEndCallback( TimerHandle_t xTimer ) {
    OBH_K03P* p = (OBH_K03P*)pvTimerGetTimerID(xTimer);
    switch(p->_cntPulse) {
    case 1:
    case 5:
    case 10:
        xQueueSend(p->_q, NULL, 0);
        return;
    default:
        // Serial.println("Banknote Reader recognize error");
        break;
    }
    p->enable();
    // Serial.printf("Banknote count pulse %d\r\n", p->_cntPulse);
    p->_cntPulse = 0;
}

static void errorOccur(OBH_K03P* p) {

}

void OBH_K03P::enable() {
    digitalWrite(_inhibitPin, HIGH);
}

void OBH_K03P::disable() {
    digitalWrite(_inhibitPin, LOW);
}

int OBH_K03P::getBillData() {
    int billData = 0;
    if (xQueueReceive(_q, NULL, 0) == pdTRUE) {
        billData = _cntPulse*1000;
        _cntPulse = 0;
    }
    return billData;
}

int OBH_K03P::initialized() {
    pinMode(_inhibitPin, OUTPUT);
    pinMode(_vendPin, INPUT_PULLUP);
    pinMode(_errorPin, INPUT_PULLUP);

    _q = xQueueCreate(16, 0);
    _timer = xTimerCreate(
         /* Just a text name, not used by the RTOS
        kernel. */
        "EnterProductNumber",
        /* The timer period in ticks, must be
        greater than 0. */
        pdMS_TO_TICKS(300),
        /* The timers will auto-reload themselves
        when they expire. */
        pdFALSE,
        /* The ID is used to store a count of the
        number of times the timer has expired, which
        is initialised to 0. */
        ( void * ) this,
        /* Each timer calls the same callback when
        it expires. */
        billDataEndCallback
    );
    attachInterrupt(_vendPin, cntPulse, FALLING, this);
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
