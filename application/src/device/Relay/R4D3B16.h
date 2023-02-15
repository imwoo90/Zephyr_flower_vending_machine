#pragma once

#include "Relay.h"

class R4D3B16 : public Relay {
private:
    uint8_t _node;
public:
    R4D3B16(uint8_t id, int numOfChannels);
    virtual uint8_t open(uint16_t addr);
    virtual uint8_t close(uint16_t addr);
    virtual ~R4D3B16() {};
};