//
// Created by Ethan Breit on 2017-07-22.
//

#pragma once

#include <string>
#include <ge/error/Error.h>
#include <glm/vec3.hpp>
#include <ge/runtime/Runtime.h>

namespace ge
{

    struct WindowConstructorInfo
    {
        int16_t width                   = 500           ;
        int16_t height                  = 500           ;
        int8_t samples                  = 4             ;
        int8_t gl_major_version         = 3             ;
        int8_t gl_minor_version         = 3             ;
        int8_t mtl_major_version        = 3             ; ///Don't know if this is necessary
        int8_t mtl_minor_version        = 3             ; ///Don't know if this is necessary
        int8_t vk_major_version         = 3             ; ///Don't know if this is necessary
        int8_t vk_minor_version         = 3             ; ///Don't know if this is necessary
        Runtime* startup_thread         = nullptr       ;
        bool has_depth_buffer			= true          ;
        bool is_forward_compatible		= true          ;
		bool hidden_cursor				= true			;
        const char *window_name			= "NULL"        ;

		glm::vec3 clear_colour          = glm::vec3(1)  ;
    };


    struct Window
    {
        //virtual Window(WindowConstructorInfo) = 0;

        //virtual ~Window() = 0;

        virtual Error init(WindowConstructorInfo) = 0;

        virtual std::string getWindowName(void) = 0;

        virtual uint8_t getSamples() = 0;

        virtual void poll() = 0;

        virtual void swap() = 0;

        virtual void makeCurrentThread(Runtime*) = 0;

        virtual void cleanup() = 0;

		virtual void mainThreadPollLoop() = 0;

        virtual void setClearColour(glm::vec3) = 0;

        virtual void clear() = 0;

        virtual void bindFrameBuffer() = 0;

        virtual bool shouldClose() = 0;

        virtual void getSize(int *, int *) = 0;
    };
}
