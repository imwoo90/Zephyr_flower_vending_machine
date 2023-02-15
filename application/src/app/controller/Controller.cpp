#include <Controller.h>

// #include <device/BanknoteReader/OBH_K03S.h>
#include <device/BanknoteReader/OBH_K03P.h>
// #include <device/Relay/UPUS_SKB.h>
#include <device/Relay/R4D3B16.h>

#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(CTRL);

static const struct device *gpio0 = DEVICE_DT_GET(DT_NODELABEL(gpio0));
static const struct gpio_dt_spec led_run = GPIO_DT_SPEC_GET(DT_NODELABEL(led_run), gpios);
static struct gpio_callback swPinCallback;

struct MessageCallbackData{
    struct k_work_delayable work;
    struct k_msgq* q;
    Message msg;
};

static void putMessageCallback( struct k_work *work ) {
    MessageCallbackData* p = (MessageCallbackData*)work;
    k_msgq_put(p->q, &p->msg, K_NO_WAIT);
    delete p;
}

void Controller::putMessage(MessageType type, int data, int delay_ms) {
    MessageCallbackData *p = new MessageCallbackData();
    p->work = Z_WORK_DELAYABLE_INITIALIZER(putMessageCallback);
    p->q = &_q; p->msg.type = type; p->msg.data = data;
    k_work_schedule(&p->work, K_MSEC(delay_ms));
}

static int channel_swMotorInterrupt;
// static void motorRoundCallback(Controller* p) {
//     p->_isISR = true;
//     if (digitalRead(2) == LOW) {
//         p->putMessage(MessageRelayClose, channel_swMotorInterrupt);
//     }
//     p->_isISR = false;
// }
static void motorRoundCallback(const struct device *port,
                    struct gpio_callback *cb,
                    gpio_port_pins_t pins) {
    Controller* p = Controller::getInstance();
    if (gpio_pin_get(gpio0, 2) == 0){
        p->putMessage(MessageRelayClose, channel_swMotorInterrupt);
    }
    LOG_INF("%s", __func__);
}

int Controller::setupMachine() {
    _machine = FlowVendingMachine::getInstance();
    // pinMode(2, INPUT);
    gpio_pin_interrupt_configure(gpio0, 2, GPIO_INPUT | GPIO_INT_EDGE_FALLING );
    // attachInterrupt(2, motorRoundCallback, FALLING, this);
    gpio_init_callback(&swPinCallback, motorRoundCallback, BIT(2));
    gpio_add_callback(gpio0, &swPinCallback);

    auto onChangedCallback = [&](std::unordered_map<std::string, std::string> data) {
        static std::unordered_map<std::string, std::string> _prevData;
        bool isSame = true;
        for (auto &cur : data) {
            auto it = _prevData.find(cur.first);
            if (it == _prevData.end()) {
                isSame = false;
                break;
            }
            if (it->second != cur.second) {
                LOG_INF("%s", cur.second.c_str());
                isSame = false;
                break;
            }
        }
        if (isSame)
            return;

        LOG_INF("%s", data["state"].c_str());
        _prevData = data;


        _display->show(data);

        //Reader enable disable controll
        if (data["BanknoteReader"] == "enable") {
            putMessage(MessageBanknoteReaderEnable, 0);
        } else if (data["BanknoteReader"] == "disable") {
            putMessage(MessageBanknoteReaderDisable, 0);
        }

        if(data["LockerType"] == "1") { // relay (Lock)
            int channel = std::stoi(data["LockerChannel"]);
            putMessage(MessageRelayOpen, channel);
            putMessage(MessageRelayClose, channel, 500);
        } else if(data["LockerType"] == "2") { // relay (mortor)
            channel_swMotorInterrupt = std::stoi(data["LockerChannel"]);
            putMessage(MessageRelayOpen, channel_swMotorInterrupt);
            putMessage(MessageRelayClose, channel_swMotorInterrupt, 7000);
            // The motorRoundCallback must be called after above code is working
        }

        if(data["LEDState"] == "on") { // relay (LED)
            int channel = std::stoi(data["LEDChannel"]);
            putMessage(MessageRelayOpen, channel);
        } else if(data["LEDState"] == "off") {
            int channel = std::stoi(data["LEDChannel"]);
            putMessage(MessageRelayClose, channel);
        }

        if(data["sysMsg"] == "DelayCall") {
            int delay = std::stoi(data["sysMsgArg_0"]);
            putMessage(MessageSystemMessage, DelayCall, delay);
        }

        if(data["deinitRelays"] == "Running") {
            deinitRelays();
        }

        if (data["isSelled"] == "OK") {
            _isSelled = true;
        }
    };
    auto onTimeoutCallback = [&](const int signal) {
        putMessage(MessageTimeout, signal);
    };

    _machine->initialize(onChangedCallback, onTimeoutCallback);
    putMessage(MessageInitial, 0);
    return 0;
}

static void _keypadOffLED(k_timer *timer) {
    Keypad_4x3* _keypad = (Keypad_4x3*)timer->user_data;
    _keypad->offLED();
}
static void _flushTimer(k_timer *timer) {
    Controller* _this = (Controller*)timer->user_data;
    _this->putMessage(MessageFlush, 0);
}
int Controller::setupKeypad() {
    enum {KEYPAD_I2C_SCL = 5, KEYPAD_I2C_SDA = 4, KEYPAD_LED = 3};
    auto onKeypadCallback = [&](const KeyState state, const char key) {
        switch(state) {
        case PRESSED:
            putMessage(MessageKeypadPress, key);
            break;
        case RELEASED:
            putMessage(MessageKeypadRelease, key);
            break;
        default:
            break;
        }
    };

    _keypad = Keypad_4x3::getInstance();
    _keypad->subscribe(onKeypadCallback);
    _keypad->offLED();

    k_timer_init(&_keypadOffLedTimer, _keypadOffLED, NULL);
    _keypadOffLedTimer.user_data = _keypad;

    k_timer_init(&_lastKeyPadReleaseTimer, _flushTimer, NULL);
    _lastKeyPadReleaseTimer.user_data = this;

    // _keypad->startPolling();
    return 0;
}

int Controller::setupBankNoteReader() {
    auto onRecognizedBankNote = [&](const int billData) {
        putMessage(MessageBanknoteRecognize, billData);
    };
    int readerMode = _machine->_database->getBanknoteReaderMode();

    if (readerMode == 1) {
        _bankNoteReader = OBH_K03P::getInstance()->setPins(12, 10, 11);
    } else if(readerMode == 2) {
        // Serial2.setPinout(8, 9);
        // Serial2.begin(9600);
        // _bankNoteReader = OBH_K03S::getInstance(Serial2);
    } else {
        LOG_INF("Reader Mode setting error");
        return -1;
    }

    _bankNoteReader->registerBillDataCallBack(onRecognizedBankNote);
    return _bankNoteReader->initialized();
}

int Controller::deinitRelays() {
    for(auto _r : _relays) {
        delete _r;
    }
    _relays.clear();
    int nRelays = _machine->_database->getNumberOfRelays();
    for (int i = 0; i < nRelays; i++) {
        int _type = _machine->_database->getRelayType(i);
        int numOfCh = _machine->_database->getNumberOfChannels(i);
        if (_type == 1) {
            _relays.push_back(new R4D3B16(i+1, numOfCh)); //i + 1 is relay address
        }
    }
    return 0;
}

int Controller::setupRelays() {
    deinitRelays();
    // for (int i = 0; i < _machine->_database->getNumberOfColumns(); i++) {
    //     putMessage(MessageRelayClose, i);
    // }
    return 0;
}

void Controller::setup() {
    _display = Display::getInstance();
    _display->begin();
    k_msleep(1000);
    // Controller loop Queue Create
    k_msgq_init(&_q, _q_buffer, sizeof(Message), 256);
    if (setupMachine() < 0) {
        return;
    }

    // Setup device
    k_msleep(1000);
    if (setupKeypad() < 0) {
        _isInitOk = false;
    }
    k_msleep(1000);
    if (setupRelays() < 0) {
        _isInitOk = false;
    }
    k_msleep(1000);
    if (setupBankNoteReader() < 0) {
        _isInitOk = false;
    }

    gpio_pin_configure_dt(&led_run, GPIO_OUTPUT_INACTIVE);
    //total setup time is 5sec for easy firmware update when running binary is dead right now after started
}

void Controller::loop() {
    Message msg;
    k_msgq_get(&_q, &msg, K_FOREVER);
    processModel(msg);
    operateDevice(msg);
}

void Controller::processModel(Message &Message) {
    switch(Message.type) {
    case MessageInitial:
        _machine->begin(_isInitOk);
        putMessage(MessageRunning, 0);
        putMessage(MessageKeypadPolling, 0);
        putMessage(MessageBanknoteReaderPolling, 0);
        break;
    case MessageKeypadPress:
        _machine->pressKey(Message.data);
        _keypad->onLED();
        if (k_timer_status_get(&_keypadOffLedTimer) == 0)
            k_timer_stop(&_keypadOffLedTimer);
        break;
    case MessageKeypadRelease:
        _machine->releaseKey(Message.data);
        k_timer_start(&_keypadOffLedTimer, K_MSEC(2*1000), K_NO_WAIT);

        if (k_timer_status_get(&_lastKeyPadReleaseTimer) == 0)
            k_timer_stop(&_lastKeyPadReleaseTimer);
        k_timer_start(&_lastKeyPadReleaseTimer, K_MSEC(10*60*1000), K_NO_WAIT);
        break;
    case MessageBanknoteRecognize:
        _machine->recognizeBanknote(Message.data);
        break;
    case MessageSystemMessage:
        _machine->systemMessage((SystemMessage)Message.data);
        break;
    case MessageTimeout:
        _machine->timeout(Message.data);
        break;
    default:
        break;
    }
}

void Controller::operateDevice(Message &Message) {
    // static PinStatus running_led = HIGH;
    switch(Message.type) {
    case MessageBanknoteReaderEnable:
        _bankNoteReader->enable();
        break;
    case MessageBanknoteReaderDisable:
        _bankNoteReader->disable();
        break;
    case MessageRunning:
        gpio_pin_toggle_dt(&led_run);
        putMessage(MessageRunning, 0, 250);
        break;
    case MessageKeypadPolling:
        _keypad->getKey();
        putMessage(MessageKeypadPolling, 0, 50);
        break;
    case MessageBanknoteReaderPolling:
        _bankNoteReader->notifyBillData();
        putMessage(MessageBanknoteReaderPolling, 0, 50);
        break;
    case MessageRelayOpen:{
        int channel = Message.data;
        auto r_ch = convertChannelToRelayFromModel(channel);
        _relays[r_ch.first]->open(r_ch.second);
        LOG_INF("relay open");
        break;
    } case MessageRelayClose: {
        int channel = Message.data;
        auto r_ch = convertChannelToRelayFromModel(channel);
        _relays[r_ch.first]->close(r_ch.second);
        LOG_INF("relay close");
        break;
    } case MessageFlush: {
        if (_isSelled) {
            _isSelled = false;
            _machine->_database->flush(TypeAll);
        }
        break;
    } default:
        break;
    }
}