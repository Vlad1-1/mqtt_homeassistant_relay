#include <iostream>
#include <yaml-cpp/yaml.h>

import seeed_board;

int main() {
    YAML::Node config;
    try {
        config = YAML::LoadFile("config.yaml");
    } catch (YAML::BadFile& e) {
        std::cerr << "Couldn't load file" << std::endl << e.what() << std::endl;
        return -1;
    }

    if (config.IsNull()) {
        std::cerr << "Config file is empty" << std::endl;
        return -1;
    }


}