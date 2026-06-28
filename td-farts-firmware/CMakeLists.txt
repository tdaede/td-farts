cmake_minimum_required(VERSION 3.13...3.27)

set(PICO_BOARD pico2)
set(PICO_PLATFORM rp2350)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(td_farts)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(td_farts
    main.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(td_farts pico_stdlib)

pico_enable_stdio_usb(td_farts 1)
pico_enable_stdio_uart(td_farts 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(td_farts)
