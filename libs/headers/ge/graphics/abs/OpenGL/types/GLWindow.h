//
// Created by Ethan Breit on 2017-07-22.
//

#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <string>
#include <ge/console/ConsoleIO.h>

#include <ge/graphics/types/Window.h>

namespace ge
{
    namespace GL
    {

        struct Window : ge::Window
        {
            Window();

            ~Window();

            Error init(WindowConstructorInfo);

            std::string getWindowName(void);

            void poll();

            void swap();

            void cleanup();

            void makeCurrentThread(Runtime*);

            bool shouldClose();

            void setClearColour(glm::vec3);

            void clear();

            void bindFrameBuffer();

			void mainThreadPollLoop();


            uint8_t getSamples();

            void getSize(int *, int *);
			GLFWwindow *_window;
        private:

            int _width;
            int _height;
            int _samples;
            int _glfwWidth;
            int _glfwHeight;
            int _majorVersion;
            int _minorVersion;
            int _isForwardCompatible;
            unsigned int _clearMask;
            bool _hasDepthBuffer;
            const char *_windowName;
            
            Runtime *_startThread;
        };
    }
}