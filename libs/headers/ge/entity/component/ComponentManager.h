#pragma once
#include <ge/entity/component/ComponentBatch.h>

namespace ge
{
    namespace ComponentManager
    {
        void registerComponentBatch(ComponentBatch*);
        bool containsComponentBatch(std::string, std::string);
        ComponentBatch* getComponentBatch(std::string, std::string);
        
    }
}
