#pragma once
#include <unordered_map>
#include <string>
#include <cstdlib>
#include <vector>
#include "ReadableMemType.h"

//TODO: Implemented nested hashmaps

namespace ge
{

	namespace GlobalMemory
    {
        struct MemItem
        {
            MemItem(void* mem, ReadableMemType::type memType)
            {
                data = mem;
                memoryType = memType;
            }

            template <typename Type> Type* getRawData()
            {

				Type* t = reinterpret_cast<Type*> (data);
                return t;
            }

            template <typename Type> Type getData()
            {
				Type t = *(reinterpret_cast<Type*> (data));
                return t;
            }

            void* data;
            ReadableMemType::type memoryType;
        };

		std::vector<std::string> getAllEntries();

		void insert(std::string, MemItem);

        void remove(std::string);

		bool exists(std::string);

        MemItem get(std::string);

        void deInit();


    }
}