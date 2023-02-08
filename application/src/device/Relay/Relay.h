#pragma once

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>

class Relay {
public:
    int _numOfChannels;

    virtual uint8_t open(uint16_t addr) = 0;
    virtual uint8_t close(uint16_t addr) = 0;
};
