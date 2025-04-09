//
// Created by vlad on 03.04.2025.
//

#include "mqtt.h"

auto connect(const Config& config) -> mqtt::async_client_ptr
{
    auto client = std::make_shared<mqtt::async_client>(config.mqtt_uri, "mqtt_relay");
    mqtt::connect_options connOpts;
    connOpts.set_clean_session(true);
    connOpts.set_user_name(config.mqtt_user);
    connOpts.set_password(config.mqtt_pass);

    std::cout << "Connecting to broker" << std::endl;
    client->connect(connOpts)->wait();
    std::cout << "Connected to MQTT broker at " << config.mqtt_uri << std::endl;

    return client;
}