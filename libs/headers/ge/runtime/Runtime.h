//
// Created by Ethan Breit on 2017-08-12.
//

#pragma once

#include <chrono>
#include <string>
#include <vector>
#include <thread>
#include <queue>
#include "GlobalRuntime.h"
#include "RuntimeGroup.h"
#include <mutex>

#define ge_START_CYCLE_HANDLER(c)   static uint64_t __cycleHandlerUUID() {static uint64_t __uuid = 0;if(__uuid==0){__uuid = ge::GlobalRuntime::genCycleHandlerUUID();}return __uuid;} static void __cycle(void *vRef, uint32_t runId){ c* ref = reinterpret_cast<c*>(vRef); switch(runId) {
#define ge_GENERATE_TRAMPOLINE(f,i) case i: ref->f(); return;
#define ge_END_CYCLE_HANDLER        default:return;}}
//TODO: Add group selection

namespace ge
{



    struct Runtime
    {
        Runtime(std::string name, uint32_t cyclesPerSecond);
		Runtime(std::string name);
        bool        unlocked = false;


        void        end();

        uint32_t    cyclesPerSecond;
        uint32_t    managesBetweenClear;

        uint16_t    getAmountOfGroups();
        uint64_t    getCyclesSinceClear();

        void        enqueFunctionStatic(void (*)());

		void        enqueFunction(std::pair<void(*)(void*), void*>);


        void        insertGroup(RuntimeGroup*);
        void        insertGroup(RuntimeGroup*, uint32_t);

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
        std::vector<RuntimeGroup*>      groups;
        std::thread                    *runtime;
        std::queue<void(*)()>			staticQueue;
		std::queue<std::pair<void(*)(void*),void*>>		queue;

    };
}