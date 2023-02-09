FILE(GLOB_RECURSE app_sources
    main.cpp
    app/controller/*.c*
    app/model/*.c*
    app/view/*.c*
    device/Releay/*.c*
    device/Keypad_4x3/*.c*
)
target_sources(app PRIVATE ${app_sources})

target_include_directories(app PRIVATE
    ./
    app/controller
    app/model
    app/view
)