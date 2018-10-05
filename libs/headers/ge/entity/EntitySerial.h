#pragma once
#include <json/json.hpp>

namespace ge
{
    struct Entity;
    struct Component;

    namespace EntitySerial
    {
        nlohmann::json serializeEntity(Entity*);
        Entity* deserializeEntity(nlohmann::json);

        nlohmann::json serializePublicVar(Component* src, std::string var);
        void deserializePublicVar(Component* dest, nlohmann::json);
        void copyPublicVar(Component* dest, Component* src, std::string var);
    }
}