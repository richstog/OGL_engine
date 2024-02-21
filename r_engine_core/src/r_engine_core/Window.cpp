#include <r_engine_core/Window.hpp>
#include <r_engine_core/Log.hpp>

#include <GL/gl.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

namespace r_engine
{
    static bool s_GLFW_initialized = false;
    Window::Window(std::string title, const unsigned int width, const unsigned height)
        : m_data({std::move(title), width, height})
    {
        int result = init();

        // ImGui init
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplOpenGL3_Init();
        ImGui_ImplGlfw_InitForOpenGL(m_pWindow, true);
    }

    Window::~Window()
    {
        shutdown();
    }

    int Window::init()
    {
        LOG_INFO("Creating window '{0}' {1}x{2}", m_data.title, m_data.width, m_data.height);

        /* Initialize the library */
        LOG_INFO("GLFW initialization");
        if (!s_GLFW_initialized)
        {
            if (!glfwInit())
            {
                LOG_CRIT("GLFW is not initialized");
                return -1;
            }
            LOG_INFO("GLFW initialized");
            s_GLFW_initialized = true;
        }
        
        /* Create a windowed mode window and its OpenGL context */
        LOG_INFO("Create window");
        m_pWindow = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), NULL, NULL);
        if (!m_pWindow)
        {
            LOG_CRIT("Window {0} was not created", m_data.title);
            glfwTerminate();
            return -2;
        }

        /* Make the window's context current */
        
        glfwMakeContextCurrent(m_pWindow);

        glfwSetWindowUserPointer(m_pWindow, &m_data);

        glfwSetWindowSizeCallback(m_pWindow,
            [](GLFWwindow* pWindow, int width, int height)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
                data.width = width;
                data.height = height;

                EventWindowResize event(width, height);
                data.eventCallBackFunc(event);
            }
        );

        glfwSetCursorPosCallback(m_pWindow,
            [](GLFWwindow* pWindow, double x, double y)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));

                EventMouseMoved event(x, y);
                data.eventCallBackFunc(event);
            }
        );

        glfwSetWindowCloseCallback(m_pWindow,
            [](GLFWwindow* pWindow)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));

                EventWindowClose event;
                data.eventCallBackFunc(event);
            }
        );

        return 0;
    }
    void Window::shutdown()
    {
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
    }

    void Window::on_update()
    {
        glClearColor(1, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize.x = static_cast<float>(get_width());
        io.DisplaySize.y = static_cast<float>(get_height());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
    }
}