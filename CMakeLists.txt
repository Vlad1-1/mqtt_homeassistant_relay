cmake_minimum_required(VERSION 3.31)
project(mqtt_homeassistant_relay)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")

set(PAHO_BUILD_STATIC CACHE BOOL TRUE "Build static library")
set(PAHO_WITH_MQTT_C CACHE BOOL TRUE "Build Paho C from the internal GIT submodule.")

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

FetchContent_Declare(
        PahoMqttCpp
        GIT_REPOSITORY https://github.com/eclipse-paho/paho.mqtt.cpp.git
        GIT_TAG v1.5.2
)
FetchContent_MakeAvailable(PahoMqttCpp)

#FetchContent_Declare(
#        yaml-cpp
#        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
#        GIT_TAG master # Can be a tag (yaml-cpp-x.x.x), a commit hash, or a branch name (master)
#)
#FetchContent_MakeAvailable(yaml-cpp)

find_package(yaml-cpp)

include_directories(headers)

add_executable(mqtt_homeassistant_relay
        src/main.cpp
        src/config.cpp

        headers/config.h
)
add_library(seeed seeed/seeed_board.cpp seeed/smbus.c)

target_link_libraries(seeed i2c)
target_link_libraries(mqtt_homeassistant_relay PUBLIC PahoMqttCpp::paho-mqttpp3 yaml-cpp::yaml-cpp seeed)

target_sources(
    seeed
    PUBLIC
    FILE_SET CXX_MODULES
        FILES
        seeed/seeed_board.cpp
)
