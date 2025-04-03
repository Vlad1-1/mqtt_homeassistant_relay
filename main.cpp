#include <iostream>
#include "yaml-cpp/yaml.h"

#include "config.h"

int main() {
    auto config_node = YAML::LoadFile("config.yaml");

    auto config = parse_config(config_node);

    std::cout << std::format("URI of the server: {}\n", config.mqtt_uri);
}