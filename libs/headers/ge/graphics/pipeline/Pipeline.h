#pragma once

#include <list>
#include <ge/runtime/RuntimeGroup.h>
#include "PipelineStage.h"

namespace ge
{
    struct PipelineRuntimeRouter : public RuntimeGroup //singleton
    {
        static PipelineRuntimeRouter* ctx;
        static void init();

        void cycle(); //override

        void signal();


    };

    struct Pipeline
    {
        std::list<PipelineStage*> stages;

        void draw();

        void pushDrawCall();

        void safeInsert();

        PipelineStage* getCurrentStage();

        PipelineState::type getState();

    private:
        std::list<PipelineStage*>::iterator currentStage;
        PipelineState::type currentState;
    };
}