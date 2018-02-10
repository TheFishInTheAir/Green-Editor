//
// Created by Ethan Breit on 2017-08-08.
//

#pragma once

#include <graphics/types/Window.h>
#include "KeyboardKey.h"

namespace ge
{
    namespace KeyboardHandler
    {


        typedef void (* KeyListener)(KeyboardKey::type, int32_t, KeyboardModifier::type, KeyboardKeyState::type);

        bool keyDown(KeyboardKey::type);
        bool keyDownSticky(KeyboardKey::type);

        void _keyHandler(GLFWwindow *, int key, int scancode, int action, int mods);

        void insertKeyListener(KeyListener);

    }
}