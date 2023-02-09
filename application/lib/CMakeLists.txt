FILE(GLOB lib_sources
    PCF8574/*.c*
    Keypad/src/*.c*
)

# u8x8_byte_arduino_hw_spi, u8x8_gpio_and_delay_arduino 포팅 해야함
FILE(GLOB_RECURSE lib_u8g2
    u8g2/src/*.c*
)

target_sources(app PRIVATE ${lib_sources} ${lib_u8g2})

target_include_directories(app PRIVATE
    ./
    PCF8574
    Keypad/src
    u8g2/src
)