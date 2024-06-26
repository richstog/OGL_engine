#pragma once

#include <string>
#include <GLFW/glfw3.h>
#include <functional>
#include <glm/ext/vector_float2.hpp>

#include "r_engine_core/Event.hpp"


namespace r_engine {
    class Window {
        public:
        using EventCallbackFunc = std::function<void(BaseEvent&)>;

        Window(std::string title, const unsigned int width, const unsigned height);
        ~Window();

        Window(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;

        void on_update();
        unsigned int get_width() const { return m_data.width; };
        unsigned int get_height() const { return m_data.height; };
        glm::vec2 get_current_cursor_position() const;

        void set_event_callback(const EventCallbackFunc& callback)
        {
            m_data.eventCallBackFunc = callback;
        }

        private:

        struct WindowData
        {
            std::string title;
            unsigned int width;
            unsigned int height;
            EventCallbackFunc eventCallBackFunc;
        };


        int init();
        void shutdown();

        GLFWwindow* m_pWindow = nullptr;
        WindowData m_data;
    };
}