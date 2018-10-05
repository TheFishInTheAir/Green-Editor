//
// Created by Ethan Breit on 2017-08-12.
//

#pragma once

#include <chrono>
#include <string>
#include <vector>
#include <thread>
#include <queue>
#include "RuntimeManager.h"
#include "RuntimeGroup.h"
#include <mutex>

#define ge_START_CYCLE_HANDLER(c)                               \
static uint64_t __cycleHandlerUUID()                            \
{                                                               \
    static uint64_t __uuid = 0;                                 \
    if(__uuid==0)                                               \
    {                                                           \
        __uuid = ge::RuntimeManager::genCycleHandlerUUID();     \
    }                                                           \
    return __uuid;                                              \
}                                                               \
static void __cycle(void *vRef, uint32_t runId)                 \
{                                                               \
    c* ref = reinterpret_cast<c*>(vRef);                        \
    switch(runId)                                               \
    {
#define ge_GENERATE_TRAMPOLINE(f,i)                             \
        case i:                                                 \
            ref->f();                                           \
            return;
#define ge_END_CYCLE_HANDLER                                    \
        default:return;                                         \
    }                                                           \
}

namespace ge
{



    struct Runtime
    {
        Runtime(std::string name, uint32_t cyclesPerSecond);
		Runtime(std::string name);
        bool        unlocked = false;

		void start();

        void        end();

        uint32_t    cyclesPerSecond;
        uint32_t    managesBetweenClear = 10;

        uint16_t    getAmountOfGroups();
        uint64_t    getCyclesSinceClear();
        uint32_t    getCyclesSinceManage();
        float       getLastDelta();
        float       getLastManagesAverageDelta();
        uint32_t    getLastManagesCycles();

        float       getTime(); //a value that goes from 0 to PI in a second

        void        enqueFunctionStatic(void (*)());

		void        enqueFunction(std::pair<void(*)(void*), void*>);


        void        insertGroup(RuntimeGroup*);
        void        insertGroup(RuntimeGroup*, uint32_t);
        RuntimeGroup* getGroup (uint32_t);

		std::string getName();

		std::thread::id getThreadID();

    private:

        static void         run(Runtime*);
		static void         runUnlocked(Runtime*);


        void                            cycle();

        bool                            shouldRun                   = true;
        std::string                     name                        = "NULL";
        uint32_t                        managesSinceLastClear       = 0;
        uint64_t                        cyclesSinceLastClear        = 0;
        uint32_t                        cyclesSinceLastManage       = 0;
        float                           smoothTime                  = 0;

        float                           miliLastDelta               = 0;
        float                           tempMiliValue               = 0;
        float                           lastManagesAverageDelta     = 0;
        uint32_t                        lastManagesCycles           = 0;
        std::vector<RuntimeGroup*>      groups; //Maybe make a bst  TODO: OPTOMIZE
        std::thread                    *runtime;
        std::queue<void(*)()>			staticQueue;
		std::queue<std::pair<void(*)(void*),void*>>		queue;

    };
}
