//
// Created by vlad on 28.03.2025.
//

#include "config.h"

#include <unordered_map>

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/iterator.h>

auto parse_config(const YAML::Node& config_node)
{
    Config cfg;

    if (!config_node.IsMap()) {
        throw std::invalid_argument("Configuration is not a map");
    }

    const auto& relays = config_node["relays"];

    if (!relays.IsSequence())
        throw std::invalid_argument("relays is not a sequence");

    for (const auto& relay : relays)
    {
        if (!relay.IsMap())
            throw std::invalid_argument("Relay is not a map");

        const auto& name = relay["name"];
        const auto& pin = relay["pin"];

        if (!name.IsScalar() || !pin.IsScalar())
            throw std::invalid_argument("Relay name or pin is not a scalar");

        const auto& pin_number = pin.as<int>();
        if (pin_number < 0 || pin_number >= RELAY_NUM)
            throw std::invalid_argument("Relay pin number is out of range");

        cfg.relay_map[name.as<std::string>()] = pin_number;
    }

    if (const auto& mqtt = config_node["mqtt"]; mqtt.IsDefined())
    {
        if (mqtt["uri"].IsDefined())
            cfg.mqtt_uri = mqtt["uri"].as<std::string>();

        cfg.mqtt_user = mqtt["user"].as<std::string>("");
        cfg.mqtt_pass = mqtt["pass"].as<std::string>("");
    }

    return cfg;
}


