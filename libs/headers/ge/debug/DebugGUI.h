#pragma once

#include <ge/runtime/Runtime.h>
#include <engine/global_settings.pre>
#include <ge/entity/Entity.h>
#include <ge/engine/enum/DataTypes.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
struct nk_context;

namespace ge
{
    namespace Debug
    {
        struct DebugGUI
        {
            
            static void enable();
            static void disable();

        private:
            static DebugGUI* ctx;
            bool isEnabled = false;

            bool shouldRender = false;
            bool shouldDrawEntTree = false;
            bool shouldDrawCurrentRes = false;
            bool shouldDrawInfoOverlay = false;
            bool shouldDrawFrameBuffers = false;

            std::string probeSaveLoc = "";
            std::string probeLoadLoc = "";
            void init();

            void draw();

            ge_START_CYCLE_HANDLER(DebugGUI)
				ge_GENERATE_TRAMPOLINE(draw, PIPELINE_ROUTER_RG)
			ge_END_CYCLE_HANDLER

            void drawEntTree();
            void drawEntProbe();

            void drawSceneProbe();

            void drawCurrentRes();
            void drawFrameBuffers();

            void drawInfoOverlay();

            //Data Type Formatting
            void dtfAuto(std::string, DataType::type, void*);
            void dtfBool(std::string, bool*);
            void dtfFloat(std::string, float*);
            void dtfInt(std::string, int*);

            void dtfMat(std::string, std::string*);
            void dtfMD(std::string, std::string*);
			void dtfAC(std::string, std::string*);

            void dtfFVEC3(std::string, glm::vec3*);
            void dtfCOL3(std::string, glm::vec3*);

            void dtfQUAT(std::string, glm::quat*);

            Entity* selectedEnt = nullptr;
            //std::string* strMatSelector = nullptr;

            //nuklear
            nk_context *nctx;

        };
    }
}