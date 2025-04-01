//
// Created by vlad on 28.03.2025.
//

#ifndef CONFIG_H
#define CONFIG_H
#include <exception>
#include <yaml-cpp/node/node.h>

struct config_exception final : std::exception {
    enum class Reason {
        CONFIG_OK,
        CONFIG_NOT_FOUND,
        CONFIG_ROOT_INVALID,
        CONFIG_RELAY_MISFORMAT,
        CONFIG_RELAY_NOT_FOUND,
    } reason{};

    explicit config_exception(Reason reason);
};

/**
 * @brief Validates the configuration file.
 * @param config The configuration file to validate.
 * @throws config_exception if the configuration is invalid.
 */
auto validate_config(YAML::Node &config) -> void;

#endif //CONFIG_H
