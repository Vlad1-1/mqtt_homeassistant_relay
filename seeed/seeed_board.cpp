//
// Created by vlad on 27.03.2025.
//

export module seeed_board;

#include <cstdio>
#include <fcntl.h>
#include <unistd.h>

#include <i2c/smbus.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

namespace relay {
    int file = -1;
    __u8 state = 0xFF;

    [[nodiscard]] auto set_address(const int i2c_address) -> int {
        return ioctl(file, I2C_SLAVE, i2c_address);
    }

    [[nodiscard]] auto open_bus(const int i2c_bus, const int i2c_address = 0x20) -> int {
        char filename[32];
        snprintf(filename, 32, "/dev/i2c-%d", i2c_bus);

        file = open(filename, O_RDWR);
        if (file < 0) {
            return file;
        }
        return set_address(i2c_address);
    }

    auto write_state() -> __s32 {
        return i2c_smbus_write_byte_data(file, 0x06, state);
    }
}

export namespace relay {
    /**
     * Opens the default I2C bus, with the default address
     *
     * @return 0 on success, a negative number on failer
     */
    [[nodiscard]] auto open_bus() -> int {
        return open_bus(1);
    }

    /**
     * Closes the I2C bus
     *
     * @return 0 on success, a negative number on failure
     */
    auto close_bus() -> int {
        if (file >= 0) {
            return close(file);
        }
        return 0;
    }

    /**
     * Turns on the specified relay
     *
     * @param relay The relay number to turn on
     * @return 0 on success, a negative number on failure
     */
    auto turn_on(const unsigned char relay) -> int {
        state &= ~(1 << relay);
        return write_state();
    }

    /**
     * Turns off the specified relay
     *
     * @param relay The relay number to turn off
     * @return 0 on success, a negative number on failure
     */
    auto turn_off(const unsigned char relay) -> int {
        state |= 1 << relay;
        return write_state();
    }

    /**
     * Toggles the specified relay
     *
     * @param relay The relay number to toggle
     * @return 0 on success, a negative number on failure
     */
    auto toggle(const unsigned char relay) -> int {
        state ^= 1 << relay;
        return write_state();
    }

    /**
     * Get the state of the specified relay
     *
     * @param relay The relay number to get the state of
     * @return The state of the relay
     */
    auto get_relay_state(const unsigned char relay) -> bool {
        return state >> relay & 1;
    }
}
