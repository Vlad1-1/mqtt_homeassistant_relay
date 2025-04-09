//
// Created by vlad on 28.03.2025.
//

#ifndef CONFIG_H
#define CONFIG_H

#pragma once

#ifndef RELAY_NUM
#define RELAY_NUM 4
#endif // RELAY_NUM

#include <unordered_map>
#include "yaml-cpp/node/node.h"

struct Config
{
    std::string mqtt_uri = "mqtt://localhost:1883";
    std::string mqtt_user;
    std::string mqtt_pass;

    std::unordered_map<std::string, int> relay_map;
};

/**
 * @brief Validates the configuration file.
 * @param config_node The yaml root node of the config file
 * @throws config_exception if the configuration is invalid.
 */
auto parse_config(const YAML::Node& config_node) -> Config;

#endif //CONFIG_H
