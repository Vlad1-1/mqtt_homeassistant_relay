cmake_minimum_required(VERSION 3.31)
project(mqtt_homeassistant_relay)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")

set(PAHO_BUILD_STATIC CACHE BOOL TRUE "Build static library")
set(PAHO_WITH_MQTT_C CACHE BOOL TRUE "Build Paho C from the internal GIT submodule.")

add_subdirectory(paho)
include_directories(paho/include)

add_executable(mqtt_homeassistant_relay main.cpp
        mqtt_connection/mqtt_connection.h
        mqtt_connection/mqtt_init.cpp
        mqtt_connection/mqtt_init.h
        config.cpp
        config.h
        config_exception.cpp
)
add_library(seeed seeed/seeed_board.ixx)

target_link_libraries(seeed i2c)
target_link_libraries(mqtt_homeassistant_relay PRIVATE paho-mqtt3a-static yaml-cpp seeed)

target_sources(
    seeed
    PUBLIC
    FILE_SET CXX_MODULES
        FILES
        seeed/seeed_board.ixx
)
