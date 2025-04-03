//
// Created by vlad on 28.03.2025.
//

#include "mqtt_init.h"
#include <iostream>
#include <memory>

#include "mqtt/async_client.h"
#include "mqtt/connect_options.h"

using namespace std;
using namespace std::chrono_literals;
using namespace mqtt;

namespace
{
    int main()
    {
        async_client("mqtt://localhost:1883");
    }
}
