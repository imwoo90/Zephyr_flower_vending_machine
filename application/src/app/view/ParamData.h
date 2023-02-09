#pragma once
#include <zephyr/kernel.h>
#include "resource.h"

struct ParamData {
    int16_t interval;
    uint16_t x, y;
    const uint8_t* font;
};

#define X(name) extern const ParamData name##_ParamDatas[];
    RESOURCES
#undef X