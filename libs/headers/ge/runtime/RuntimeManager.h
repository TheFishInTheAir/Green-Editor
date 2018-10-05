//
// Created by Ethan Breit on 2017-08-13.
//

#pragma once

#include <cstdint>
#include <string>

//TODO: MAKE INLINE FUNCTION \/
#define ge_REGISTER_RUNTIME_HANDLER                                 \
ge::RuntimeManager::registerHandler(__cycleHandlerUUID(), __cycle);

namespace ge
{
	struct Runtime;

    namespace RuntimeManager
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


		void registerRuntime(Runtime*);
		Runtime* getRuntime(std::string);
		void removeRuntime(std::string);

        uint64_t genCycleHandlerUUID();

        void registerHandler(uint64_t,void(*)(void*, uint32_t));
        RuntimeHandler* getHandler(uint64_t);


    }

}
