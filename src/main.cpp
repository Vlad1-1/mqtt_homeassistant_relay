#include <iostream>
#include <yaml-cpp/yaml.h>

#include "config.h"
#include "mqtt/async_client.h"

constexpr std::string DEFAULT_ID{"relay"};

int main() {
    const auto config_node = YAML::LoadFile("config.yaml");
    const Config config = parse_config(config_node);

    std::cout << std::format("URI of the server: {}\n", config.mqtt_uri);

    auto conn_opts = mqtt::connect_options_builder()
        .clean_start(false)
        .user_name(config.mqtt_user)
        .password(config.mqtt_pass)
        .finalize();

    auto client = std::make_shared<mqtt::async_client>(config.mqtt_uri, DEFAULT_ID);

}
