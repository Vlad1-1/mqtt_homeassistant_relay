//
// Created by vlad on 28.03.2025.
//

#include <exception>

struct config_exception final : std::exception {
    enum class Reason {
        CONFIG_OK,
        CONFIG_NOT_FOUND,
        CONFIG_ROOT_INVALID,
        CONFIG_RELAY_MISFORMAT,
        CONFIG_RELAY_NOT_FOUND,
    } reason{};

    explicit config_exception(const Reason reason) : reason(reason) {}

    [[nodiscard]] const char *what() const noexcept override {
        switch (reason) {
            case Reason::CONFIG_OK:
                return "Config is ok";
            case Reason::CONFIG_NOT_FOUND:
                return "Config not found";
            case Reason::CONFIG_ROOT_INVALID:
                return "Config root invalid";
            case Reason::CONFIG_RELAY_MISFORMAT:
                return "Relay misformatted";
            case Reason::CONFIG_RELAY_NOT_FOUND:
                return "Relay not found";
        }
        return "Unknown error";
    }
};
