//
// Created by Ethan Breit on 2017-07-22.
//

#pragma once

#include <string>
#include <error/Error.h>
#include <glm/vec3.hpp>
#include <runtime/Runtime.h>

namespace ge
{

    struct WindowConstructorInfo
    {
        int16_t width                   = 500           ;
        int16_t height                  = 500           ;
        int8_t samples                 = 4             ;
        int8_t glMajorVersion          = 3             ;
        int8_t glMinorVersion          = 3             ;
        int8_t mtlMajorVersion         = 3             ; ///Don't know if this is necessary
        int8_t mtlMinorVersion         = 3             ; ///Don't know if this is necessary
        int8_t vkMajorVersion          = 3             ; ///Don't know if this is necessary
        int8_t vkMinorVersion          = 3             ; ///Don't know if this is necessary
        Runtime* startupThread         = nullptr       ;
        bool hasDepthBuffer         = true          ;
        bool isForwardCompatible    = true          ;
		bool hiddenCursor			= true			;
        const char *windowName      = "NULL"        ;
    };


    struct Window
    {
        //virtual Window(WindowConstructorInfo) = 0;

        //virtual ~Window() = 0;

        virtual Error init(WindowConstructorInfo) = 0;

        virtual std::string getWindowName(void) = 0;

        virtual void poll() = 0;

        virtual void swap() = 0;

        virtual void makeCurrentThread(Runtime*) = 0;

        virtual void cleanup() = 0;

        virtual void setClearColour(glm::vec3) = 0;

        virtual void clear() = 0;

        virtual bool shouldClose() = 0;

        virtual void getSize(int *, int *) = 0;
    };
}