FILE(GLOB lib_sources
    PCF8574/*.c*
    Keypad/src/*.c*
)
target_sources(app PRIVATE ${lib_sources})

target_include_directories(app PRIVATE
    ./
    PCF8574
    Keypad/src
)