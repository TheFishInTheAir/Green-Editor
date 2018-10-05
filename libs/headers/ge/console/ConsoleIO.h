//
// Created by Ethan Breit on 2017-07-22.
//

#pragma once

#include <ge/console/enum/MessageType.h>
#include <string>

namespace ge
{
    namespace ConsoleIO
    {

        void print(std::string);
        void print(std::string, MessageType::type);
    }
}