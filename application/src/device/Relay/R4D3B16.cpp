#include "R4D3B16.h"

static int client_iface;

R4D3B16::R4D3B16(uint8_t id, int numOfChannels) {
    _numOfChannels = numOfChannels;
    _node = id;
}

uint8_t R4D3B16::open(uint16_t addr) {
    // uint8_t ret = node.writeSingleRegister(addr, 0x0100);
    uint8_t ret = modbus_write_holding_reg(client_iface, _node, addr, 0x0100);
    delay(50);
    return ret;
}

uint8_t R4D3B16::close(uint16_t addr) {
    // uint8_t ret = node.writeSingleRegister(addr, 0x0200);
    uint8_t ret = modbus_write_holding_reg(client_iface, _node, addr, 0x0200);
    delay(50);
    return ret;
}

static int init_modbus_client(const struct device *dev)
{
    ARG_UNUSED(dev);
#define MODBUS_NODE DT_COMPAT_GET_ANY_STATUS_OKAY(zephyr_modbus_serial)
    const char iface_name[] = {DEVICE_DT_NAME(MODBUS_NODE)};
    const struct modbus_iface_param client_param = {
        .mode = MODBUS_MODE_RTU,
        .rx_timeout = 500,
        .serial = {
            .baud = 9600,
            .parity = UART_CFG_PARITY_NONE,
            .stop_bits_client = UART_CFG_STOP_BITS_1,
        },
    };
    client_iface = modbus_iface_get_by_name(iface_name);

    return modbus_init_client(client_iface, client_param);
}

SYS_INIT(init_modbus_client, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);