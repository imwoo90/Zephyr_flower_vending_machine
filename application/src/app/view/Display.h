#pragma once

#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>

#include <string>
#include <unordered_map>

#include "resource.h"

class Display {
private:
    U8G2_ST75256_JLX256160_F_4W_HW_SPI u8g2;
    Display() : u8g2(U8G2_R0, /* cs=*/ 17, /* dc=*/ 21, /* reset=*/ 20)// Enable U8g2 16 bit mode for this display)
    {}

    void drawBackground(ResourceType background);
    void drawParamDatas(ResourceType background, std::unordered_map<std::string, std::string> &data);
public:

    void begin() {
        SPI.setSCK(18);
        SPI.setTX(19);
        u8g2.begin();
    }
    static Display* getInstance() {
        static Display singleton_instance;
        return &singleton_instance;
    }

    void show(std::unordered_map<std::string, std::string> &data);
};