//
// Created by vlad on 28.03.2025.
//

#include "config.h"

#include <yaml-cpp/node/iterator.h>

auto validate_config(YAML::Node &config) -> void {
    if (!config.IsMap()) {
        throw config_exception(config_exception::Reason::CONFIG_ROOT_INVALID);
    }

    const auto &relays = config["relays"];

    if (!relays.IsSequence())
        throw config_exception(config_exception::Reason::CONFIG_RELAY_NOT_FOUND);

    for (auto it = relays.begin(); it != relays.end(); ++it) {
        if (!it->IsMap() || !(*it)["name"].IsScalar() || !(*it)["pin"].IsScalar())
            throw config_exception(config_exception::Reason::CONFIG_RELAY_MISFORMAT);
    }
}
