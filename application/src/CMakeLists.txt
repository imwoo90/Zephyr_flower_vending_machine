FILE(GLOB_RECURSE app_sources
    main.cpp
    app/controller/*.c*
    app/model/*.c*
    app/view/*.c*
    device/Relay/*.c*
    device/Keypad_4x3/*.c*
    device/BanknoteReader/OBH_K03P.cpp
    device/BanknoteReader/BanknoteReader.cpp
)
target_sources(app PRIVATE ${app_sources})

target_include_directories(app PRIVATE
    ./
    app/controller
    app/model
    app/view
)