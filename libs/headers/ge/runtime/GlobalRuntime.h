//
// Created by Ethan Breit on 2017-08-13.
//

#pragma once

#include <cstdint>

#define ge_REGISTER_RUNTIME_HANDLER registerHandler(__cycleHandlerUUID(), __cycle);

namespace ge
{

    namespace GlobalRuntime
    {

        struct RuntimeHandler
        {
            uint64_t uuid;

            void (*func)(void *, uint32_t);
        };


        struct RuntimeItem
        {
            RuntimeHandler *handler;
            void *ref;
        };


        uint64_t genCycleHandlerUUID();

        void registerHandler(uint64_t,void(*)(void*, uint32_t));
        RuntimeHandler* getHandler(uint64_t);


    }

}