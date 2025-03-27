cmake_minimum_required(VERSION 3.31)
project(mqtt_homeassistant_relay)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")

add_subdirectory(paho)

add_executable(mqtt_homeassistant_relay main.cpp)

target_sources(
    mqtt_homeassistant_relay
    PUBLIC
    FILE_SET CXX_MODULES
        FILES
            ${CMAKE_CURRENT_SOURCE_DIR}/seeed_board.ixx
)
