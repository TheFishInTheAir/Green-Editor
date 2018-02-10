//
// Created by Ethan Breit on 2017-08-12.
//

#pragma once

#include <functor/Functor.h>
#include <list>
#include "GlobalRuntime.h"

#define ge_RUNTIME_GROUP_INSERT_THIS insert(this, __cycleHandlerUUID())
#define ge_RUNTIME_GROUP_INSERT_STACK(r) insert(r, r.__cycleHandlerUUID())
#define ge_RUNTIME_GROUP_INSERT_HEAP(r) insert(r, r->__cycleHandlerUUID())
//TODO: Add Other Definitions
#define ge_RUNTIME_GROUP_REMOVE_THIS remove(this)
#define ge_RUNTIME_GROUP_REMOVE_HEAP(r) remove(r)

namespace ge
{
    using namespace GlobalRuntime;


    struct RuntimeGroup
    {
        uint32_t        runtimeId;

        void            cycle();

        void            insert(void *, uint64_t);

        void            remove(void *);
    private:
        std::list<RuntimeItem> items;
    };
}