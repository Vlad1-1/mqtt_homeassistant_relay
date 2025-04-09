//
// Created by vlad on 03.04.2025.
//

#ifndef MQTT_H
#define MQTT_H

#include "config.h"
#include "mqtt/async_client.h"

/**
 * @brief Connects to the mqtt broker using the provided config.
 *
 * @param config Parsed config from the input file
 * @return A shared pointer to the mqtt::async_client
 */
auto connect(const Config& config) -> mqtt::async_client_ptr;

#endif //MQTT_H
