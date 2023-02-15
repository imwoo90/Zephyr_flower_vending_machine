#ifndef CONTROLLER_H
#define CONTRALLER_H

#include <zephyr/kernel.h>

#include <FlowVendingMachine.h>
#include <device/Keypad_4x3/Keypad_4x3.h>
#include <device/BanknoteReader/BanknoteReader.h>
#include <device/Relay/Relay.h>
#include <Display.h>

#include <vector>


typedef enum {
    MessageInitial,
    MessageKeypadPress,
    MessageKeypadRelease,
    MessageBanknoteRecognize,
    MessageSystemMessage,
    MessageTimeout,

    MessageBanknoteReaderEnable,
    MessageBanknoteReaderDisable,
    MessageRelayOpen,
    MessageRelayClose,
    MessageRunning,
    MessageKeypadPolling,
    MessageBanknoteReaderPolling,
    MessageFlush,
    MessageTEST,
} MessageType;

struct Message {
    MessageType type;
    int data;
};

class Controller {
private:
    bool _isSelled = false;

    int _isInitOk = true;

    k_msgq _q;
    char __aligned(4) _q_buffer[256*sizeof(Message)];
    k_timer _keypadOffLedTimer;
    k_timer _lastKeyPadReleaseTimer;

    Display* _display;

    FlowVendingMachine* _machine;
    Keypad_4x3* _keypad;
    BanknoteReader* _bankNoteReader;
    std::vector<Relay*> _relays;

    int setupKeypad();
    int setupBankNoteReader();
    int deinitRelays();
    int setupRelays();
    int setupMachine();

    std::pair<int, int> convertChannelToRelayFromModel(int channel) {
        /*
            param channel is started from 1
            and relay address start is 1 and the relay index is 0
            so param channel is 1 convert to relay idx 0 and relay channel is 1
        */
        int idx = 0;
        // channel -= 1; // change channel start to 0
        while(channel >= _relays[idx]->_numOfChannels) {
            channel -= _relays[idx]->_numOfChannels;
            idx += 1;
        }
        return std::pair<int, int>(idx, channel+1);
    }

    void processModel(Message &message);
    void operateDevice(Message &message);

    Controller() {}
public:
    static Controller* getInstance() {
        static Controller singleton_instance;
        return &singleton_instance;
    }

    bool _isISR = false;
    void putMessage(MessageType type, int data, int delay_ms = 0);

    void setup();
    void loop();
};

#endif