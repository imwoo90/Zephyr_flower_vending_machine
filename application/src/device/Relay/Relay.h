#pragma once

#include <zephyr/kernel.h>

class Relay {
public:
    int _numOfChannels;

    virtual uint8_t open(uint16_t addr) = 0;
    virtual uint8_t close(uint16_t addr) = 0;
    virtual ~Relay() {};
};
