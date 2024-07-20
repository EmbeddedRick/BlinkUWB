cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(BlinkUWB)

#target_sources(app PRIVATE src/main.c)
FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})
 
# To adding custom folders
target_sources(app PRIVATE src/lib/decadriver/deca_device.c)
target_sources(app PRIVATE src/lib/decadriver/deca_params_init.c)
zephyr_include_directories(src/lib/decadriver)
target_sources(app PRIVATE src/lib/platform/port.c)
target_sources(app PRIVATE src/lib/platform/deca_spi.c)
zephyr_include_directories(src/lib/platform)
