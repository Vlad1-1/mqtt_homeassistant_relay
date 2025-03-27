cmake_minimum_required(VERSION 3.31)
project(mqtt_homeassistant_relay)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")

set(PAHO_BUILD_STATIC CACHE BOOL TRUE "Build static library")
set(PAHO_WITH_MQTT_C CACHE BOOL TRUE "Build Paho C from the internal GIT submodule.")

add_subdirectory(paho)

add_executable(mqtt_homeassistant_relay main.cpp)
target_link_libraries(mqtt_homeassistant_relay PRIVATE paho-mqtt3a)

target_sources(
    mqtt_homeassistant_relay
    PUBLIC
    FILE_SET CXX_MODULES
        FILES
            ${CMAKE_CURRENT_SOURCE_DIR}/seeed_board.ixx
)
