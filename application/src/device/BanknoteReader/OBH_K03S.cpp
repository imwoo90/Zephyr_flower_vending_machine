#include "OBH_K03S.h"
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(obh_k03s);

#define FIFO_SIZE 256
static uint8_t fifo_buf[FIFO_SIZE];
static uint32_t fifo_head;
static uint32_t fifo_tail;
static uint32_t fifo_count;

static void uart_cb_handler(const struct device *dev, void *app_data)
{
    if (uart_irq_update(dev) && uart_irq_is_pending(dev)) {
        if (uart_irq_rx_ready(dev)) {
            uint8_t c;
            uart_fifo_read(dev, &c, 1);
            if (fifo_count < FIFO_SIZE) {
                fifo_buf[fifo_head++] = c;
                fifo_head %= FIFO_SIZE;
                fifo_count++;
            } else {
                // FIFO buffer overflow, handle error
            }
        }
    }
}

void OBH_K03S::sendBytes(const char* buf, uint32_t len) {
    for (uint32_t i = 0; i < len; i++) {
        uart_poll_out(_serial, buf[i]);
    }
}

int OBH_K03S::readBytes(char* buf, uint32_t len, uint32_t timeout_ms) {
    uint32_t start = k_uptime_get_32();
    while(1){
        if (k_uptime_get_32() - start > timeout_ms)
            return false;

        if (fifo_count >= len) {
            break;
        }
        k_msleep(1);
    }

    for (uint32_t i = 0; i < len; i++) {
        buf[i] = fifo_buf[fifo_tail++];
        fifo_tail %= FIFO_SIZE;
        fifo_count--;
    }
    return true;
}

#define checksum(x) (char)((x)[1]+(x)[2]+(x)[3])

bool OBH_K03S::receiveCommnad(const char* _buf, const char* cmd) {
    return _buf[1] == cmd[0] && _buf[2] == cmd[1];
}
void OBH_K03S::sendCommand(const char* cmd) {
    char _buf[5] = {
        '$', cmd[0], cmd[1], cmd[2]
    };
    _buf[4] = checksum(_buf);
    sendBytes(_buf, 5);
    LOG_INF("write %c %c %c %d %d", _buf[0], _buf[1], _buf[2], _buf[3], _buf[4]);
}

int OBH_K03S::initialized() {
    int err = uart_irq_callback_set(_serial, uart_cb_handler);
    if (err) {
        LOG_INF("Failed to set UART callback: %d", err);
        return err;
    }
    uart_irq_rx_enable(_serial);

    char _buf[5];
    while(readBytes(_buf, 1, 1)); //Flush uart rx buffer
    //reset
    char cmd[3] = {'R', 'S', 'T'};
    sendCommand(cmd);
    readBytes(_buf, 5, 300);
    if (!receiveCommnad(_buf, "OK")) {
        // Serial.println("OHB_K03S reset error");
        LOG_INF("OHB_K03S reset error %d", fifo_count);
        LOG_INF("%c %c %c %c %c", _buf[0], _buf[1], _buf[2], _buf[3], _buf[4]);
        return -1;
    }
    k_msleep(2500);

    // full duplex mode, auto stacking, 1000, 5000, 10000
    // set config 0x37
    cmd[0] = 'S'; cmd[1] = 'C'; cmd[2] = 0x37;
    sendCommand(cmd);
    readBytes(_buf, 5, 300);
    if (!receiveCommnad(_buf, "OK")) {
        LOG_INF("OHB_K03S config error");
        return -1;
    }

    BanknoteReader::initialized();
    return 0;
}

int OBH_K03S::getBillData() {
    char _buf[5];

    while(1) {
        if (process(_buf) < 0)
            return 0;

        if (receiveCommnad(_buf, "gb")) { //Receive BillData
            return _buf[3]*1000;
        }
    }

    return 0;
}

void OBH_K03S::enable() {
    char cmd[3] = {'S', 'A', 0x0d};
    sendCommand(cmd);
}

void OBH_K03S::disable() {
    char cmd[3] = {'S', 'A', 0x0e};
    sendCommand(cmd);
}

int OBH_K03S::process(char _buf[5]) {
    if (!readBytes(_buf, 5, 1)) {
        return -1;
    }
    LOG_INF("read %c %c %c %d %d", _buf[0], _buf[1], _buf[2], _buf[3], _buf[4]);
    if (checksum(_buf) != _buf[4]) {
        LOG_INF("OHB_K03S checksum error");
        return -1;
    }

    if (receiveCommnad(_buf, "ES")) { //Receive Event Tx
        //Ack
        char ack[3] = {'e', 's', _buf[3]};
        sendCommand(ack);

        ActiveStatus reg = (ActiveStatus)_buf[3];
        activeStatusProcess(reg);
    } else if (receiveCommnad(_buf, "gb")) { //Receive BillData
        LOG_INF("OHB_K03S billData 0x%2x", _buf[3]);
    } else {
        return -1;
    }
    return 0;
}

int OBH_K03S::activeStatusProcess(ActiveStatus reg) {
    switch (reg)
    {
    case STACK_END:
        sendCommand("GB?");
        break;
    default:
        break;
    }
    return 0;
}

 OBH_K03S* OBH_K03S::getInstance(const struct device* serial) {
    static OBH_K03S singleton_instance;
    singleton_instance._serial = serial;
    singleton_instance._name = "OBH_K03S";
    return &singleton_instance;
}