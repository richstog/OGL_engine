#pragma once

#include <r_engine_core/Keys.hpp>
#include <stddef.h>

namespace r_engine
{
    class Input
    {
        public:
        static bool IsKeyPressed(const KeyCode key_code);
        static void PressKey(const KeyCode key_code);
        static void ReleasedKey(const KeyCode key_code);

        static bool isMouseButtonPressed(const MouseButtonCode mouse_button);
        static void PressMouseButton(const MouseButtonCode mouse_button);
        static void ReleaseMouseButton(const MouseButtonCode mouse_button);

        private:
        static bool m_keys_pressed[];
        static bool m_mouse_buttons_pressed[];
    };
}