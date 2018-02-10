//
// Created by Ethan Breit on 2017-08-08.
//
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma once
namespace ge
{
    namespace KeyboardKeyState
    {
        typedef enum
        {
            Pressed = GLFW_PRESS,
            Held = GLFW_REPEAT,
            Releassed = GLFW_RELEASE
        } type;
    }

    namespace KeyboardModifier
    {
        typedef enum
        {

            Shift   = GLFW_MOD_SHIFT,
            Alt     = GLFW_MOD_ALT,
            Control = GLFW_MOD_CONTROL,
            Super   = GLFW_MOD_SUPER

        } type;

    }

    namespace KeyboardKey
    {
        typedef enum
        {
            A = GLFW_KEY_A,
            B = GLFW_KEY_B,
            C = GLFW_KEY_C,
            D = GLFW_KEY_D,
            E = GLFW_KEY_E,
            F = GLFW_KEY_F,
            G = GLFW_KEY_G,
            H = GLFW_KEY_H,
            I = GLFW_KEY_I,
            J = GLFW_KEY_J,
            K = GLFW_KEY_K,
            L = GLFW_KEY_L,
            M = GLFW_KEY_M,
            N = GLFW_KEY_N,
            O = GLFW_KEY_O,
            P = GLFW_KEY_P,
            Q = GLFW_KEY_Q,
            R = GLFW_KEY_R,
            S = GLFW_KEY_S,
            T = GLFW_KEY_T,
            U = GLFW_KEY_U,
            V = GLFW_KEY_V,
            W = GLFW_KEY_W,
            X = GLFW_KEY_X,
            Y = GLFW_KEY_Y,
            Z = GLFW_KEY_Z,
            N0 = GLFW_KEY_0,
            N1 = GLFW_KEY_1,
            N2 = GLFW_KEY_2,
            N3 = GLFW_KEY_3,
            N4 = GLFW_KEY_4,
            N5 = GLFW_KEY_5,
            N6 = GLFW_KEY_6,
            N7 = GLFW_KEY_7,
            N8 = GLFW_KEY_8,
            N9 = GLFW_KEY_9,
			F1 = GLFW_KEY_F1,
			F2 = GLFW_KEY_F2,
			F3 = GLFW_KEY_F3,
			F4 = GLFW_KEY_F4,
			F6 = GLFW_KEY_F6,
			F7 = GLFW_KEY_F7,
			F8 = GLFW_KEY_F8,
			F9 = GLFW_KEY_F9,
			F10 = GLFW_KEY_F10,
			F11 = GLFW_KEY_F11,
			F12 = GLFW_KEY_F12,
            MINUS = GLFW_KEY_MINUS,
            EQUAL = GLFW_KEY_EQUAL,
            UP = GLFW_KEY_UP,
            DOWN = GLFW_KEY_DOWN,
            LEFT = GLFW_KEY_LEFT,
            RIGHT = GLFW_KEY_RIGHT,
            ESC = GLFW_KEY_ESCAPE,
            SPACE = GLFW_KEY_SPACE,
            LSHIFT = GLFW_KEY_LEFT_SHIFT,
            RSHIFT = GLFW_KEY_RIGHT_SHIFT,
            TAB = GLFW_KEY_TAB,
            LCTRL = GLFW_KEY_LEFT_CONTROL,
            RCTRL = GLFW_KEY_RIGHT_CONTROL,
            TILDA = GLFW_KEY_GRAVE_ACCENT,
            BACKSPACE = GLFW_KEY_BACKSPACE,
            RETURN = GLFW_KEY_ENTER,
            //TODO: add in more keys


        } type;
    }
}