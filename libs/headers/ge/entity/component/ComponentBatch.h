#pragma once
#include "Component.h"
#include <vector>
#include <queue>


namespace ge
{
    //TODO: make abstract super class and make this default batch
	struct ComponentBatch
	{
		virtual void cycle() = 0;

        virtual void setComponentType(std::string);
        
        virtual std::string getBatchType();
        virtual std::string getComponentType();
        
		virtual void softInsert(Component*) = 0;
		virtual void softRemove(Component*) = 0;
        virtual void softRemove(uint32_t) = 0;
        
		virtual uint32_t hardInsert(Component*) = 0;
		virtual void hardRemove(uint32_t) = 0;
        
    protected:
        void setBatchType(std::string);
        
        std::string batchType       = "UNDEFINED";
        std::string componentType   = "UNDEFINED";
	};
}
