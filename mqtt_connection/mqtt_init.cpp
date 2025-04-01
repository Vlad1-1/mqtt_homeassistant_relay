//
// Created by vlad on 28.03.2025.
//

#include "mqtt_init.h"
#include <iostream>
#include <memory>

#include <yaml-cpp/exceptions.h>
#include <yaml-cpp/node/node.h>

#include "mqtt/async_client.h"
#include "mqtt/connect_options.h"

using namespace std;
using namespace std::chrono_literals;

auto get_connection(const YAML::Node &mqtt_config) {
    if (!mqtt_config.IsDefined()) {
        throw std::invalid_argument("Mqtt configuration missing");
    }

    auto server_uri = mqtt_config["uri"].as<std::string>();

    auto client = std::make_shared<mqtt::async_client>(server_uri, "relay_user");

    client->set_disconnected_handler([] (const mqtt::properties&, const mqtt::ReasonCode rc) {
        if (rc == mqtt::ReasonCode::SUCCESS) {
            cout << "Disconnected successfully" << endl;
        } else {
            cout << "Disconnected with error code: " << rc << endl;
        }
    });

    std::string username, password;

    try {
        username = mqtt_config["user"].as<std::string>();
        password = mqtt_config["pass"].as<std::string>();
    } catch (YAML::InvalidNode&) {
        cout << "Didn't find mqtt username or password, connecting anonymously" << endl;
        username = password = "";
    }

    auto connOpts = mqtt::connect_options_builder()
            .user_name(username)
            .password(password)
            .connect_timeout(10s)
            .finalize();

    cout << format("Connecting to {}\n", server_uri);
    try {
        const auto connection_token = client->connect(connOpts);
        connection_token->wait();
        cout << format("Connected to {}\n", server_uri);
    } catch (const mqtt::exception &e) {
        cerr << e.what() << endl;
    }

    return client;
}
