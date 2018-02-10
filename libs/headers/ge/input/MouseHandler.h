//
// Created by Ethan Breit on 2017-08-08.
//

#pragma once
#include <graphics/types/Window.h>
#include <GLFW/glfw3.h>

namespace ge
{
    namespace MouseHandler
    {
	    inline bool moveMouse = false;
		inline bool centerMouse = false;

        //TODO: Add More Input Functions (I.E. Listeners and Mouse Buttons)
        void _mouseHandler(GLFWwindow* window, double xpos, double ypos);
        void getMousePos(double*,double *);
        void resetMousePos();
    }
}