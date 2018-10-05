//
// Created by Ethan Breit on 2017-08-12.
//

#pragma once

#include <list>
#include "RuntimeManager.h"

#define ge_RUNTIME_GROUP_INSERT_THIS        insert(this, __cycleHandlerUUID())
#define ge_RUNTIME_GROUP_INSERT_STACK(r)    insert(r, r.__cycleHandlerUUID())
#define ge_RUNTIME_GROUP_INSERT_HEAP(r)     insert(r, r->__cycleHandlerUUID())

#define ge_RUNTIME_GROUP_REMOVE_THIS        remove(this)
#define ge_RUNTIME_GROUP_REMOVE_HEAP(r)     remove(r)

namespace ge
{


    struct RuntimeGroup
    {
        uint32_t        runtimeId;

        virtual void            cycle();

        virtual void            insert(void *, uint64_t);

        virtual void            remove(void *);
    protected:
        std::list<RuntimeManager::RuntimeItem> items;
    };
}
