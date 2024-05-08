#pragma once

#include <functional>
#include <array>

#include <r_engine_core/Keys.hpp>

namespace r_engine
{
    enum class EventType
    {
        WindowResized = 0,
        WindowClose,

        KeyPressed,
        KeyReleased,

        MouseButtonPressed,
        MouseButtonRealeased,
        MouseMoved,

        EventsCount
    };

    struct BaseEvent
    {
        virtual ~BaseEvent() = default;
        virtual EventType get_type() const = 0;
    };

    class EventDispatcher{
        public:
        template <typename EventType>
        void add_event_listener(std::function<void(EventType&)> callback)
        {
            auto baseCallback = [func = std::move(callback)] (BaseEvent& e)
            {
                if (e.get_type() == EventType::type)
                {
                    func(static_cast<EventType&>(e));
                }
            };
            m_eventCallbacks[static_cast<size_t>(EventType::type)] = std::move(baseCallback);
        }

        void dispatch(BaseEvent& event)
        {
            auto& callback = m_eventCallbacks[static_cast<size_t>(event.get_type())];
            if (callback)
            {
                callback(event);
            }
        }

        private:
        std::array<std::function<void(BaseEvent&)>, static_cast<size_t>(EventType::EventsCount)> m_eventCallbacks;
    };

    struct EventMouseMoved : public BaseEvent
    {
        EventMouseMoved(const double new_x, const double new_y)
        : x(new_x), y(new_y)
        {

        }

        virtual EventType get_type() const override
        {
            return type;
        }

        double x, y;

        static const EventType type = EventType::MouseMoved;
    };

    struct EventWindowResize : public BaseEvent
    {
        EventWindowResize(const unsigned int new_width, const unsigned int new_height)
        : width(new_width), height(new_height)
        {

        }

        virtual EventType get_type() const override
        {
            return type;
        }

        unsigned int width, height;

        static const EventType type = EventType::WindowResized;
    };

    struct EventWindowClose : BaseEvent
    {
        virtual EventType get_type() const override
        {
            return type;
        }

        static const EventType type = EventType::WindowClose;
    };
    
    struct EventKeyPressed : public BaseEvent
    {
        EventKeyPressed(const KeyCode key_code, const bool repeated)
        : key_code(key_code), repeated(repeated)
        {

        }

        virtual EventType get_type() const override
        {
            return type;
        }

        KeyCode key_code;
        bool repeated;

        static const EventType type = EventType::KeyPressed;
    };

    struct EventKeyReleased : public BaseEvent
    {
        EventKeyReleased(const KeyCode key_code)
        : key_code(key_code)
        {

        }

        virtual EventType get_type() const override
        {
            return type;
        }

        KeyCode key_code;

        static const EventType type = EventType::KeyReleased;
    };

    struct EventMouseButtonPressed : public BaseEvent
    {
        EventMouseButtonPressed(const MouseButtonCode mouse_button_code, const double x_pos, const double y_pos)
        : mouse_button_code(mouse_button_code), x_pos(x_pos), y_pos(y_pos)
        {

        }

        virtual EventType get_type() const override
        {
            return type;
        }

        MouseButtonCode mouse_button_code;
        double x_pos;
        double y_pos;

        static const EventType type = EventType::MouseButtonPressed;
    };

    struct EventMouseButtonRealeased : public BaseEvent
    {
        EventMouseButtonRealeased(const MouseButtonCode mouse_button_code, const double x_pos, const double y_pos)
        : mouse_button_code(mouse_button_code), x_pos(x_pos), y_pos(y_pos)
        {

        }

        virtual EventType get_type() const override
        {
            return type;
        }

        MouseButtonCode mouse_button_code;
        double x_pos;
        double y_pos;

        static const EventType type = EventType::MouseButtonRealeased;
    };
}