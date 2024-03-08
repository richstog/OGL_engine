/*
    DEFINE
    NON_INTERFACE - program starting without imgui
*/

#define GLFW_INCLUDE_NONE

#include <r_engine_core/Window.hpp>
#include <r_engine_core/Log.hpp>
#include <r_engine_core/Rendering/OpenGL/ShaderProgram.hpp>
#include <r_engine_core/Rendering/OpenGL/VertexBuffer.hpp>
#include <r_engine_core/Rendering/OpenGL/IndexBuffer.hpp>
#include <r_engine_core/Rendering/OpenGL/VertexArray.hpp>

#include <glad/glad.h>


#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

// Инициализация матриц по столбцам
#include <glm/mat3x3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace r_engine
{
    static bool s_GLFW_initialized = false;

    GLfloat positions_colors[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f,

        0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };

    GLfloat positions_colors2[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f
    };

    GLuint indexes[] = {
        0, 1, 2, 3, 2, 1
    };

    const char* vertex_shader =
        R"(
            #version 460
            layout(location = 0) in vec3 vertex_position;
            layout(location = 1) in vec3 vertex_color;
            uniform mat4 model_m;
            
            out vec3 color;
            void main() {
               color = vertex_color;
               gl_Position = model_m * vec4(vertex_position, 1.0);
            }
        )";

    const char* fragment_shader =
        R"(
            #version 460
            in vec3 color;
            out vec4 frag_color;
            void main() {
               frag_color = vec4(color, 1.0);
            }
        )";

    std::unique_ptr<ShaderProgram> p_shader_program;
    std::unique_ptr<VertexBuffer> p_positions_colors_vbo;
    std::unique_ptr<IndexBuffer> p_index_buffer;
    std::unique_ptr<VertexArray> p_vao;
    //float scale[3] = {1.f, 1.f, 1.f};
    glm::vec3 scale(1.f, 1.f, 1.f);
    float rotate = 0.f;
    //float translate[3] = {0.f, 0.f, 1.f};
    glm::vec3 translate(0.f, 0.f, 1.f);

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

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            LOG_CRIT("GLAD is not initialized");
            return -1;
        }

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

        glfwSetFramebufferSizeCallback(m_pWindow,
            [](GLFWwindow* pWindow, int width, int height)
            {
                glViewport(0, 0, width, height);
            }
        );

        p_shader_program = std::make_unique<ShaderProgram>(vertex_shader, fragment_shader);
        if (!p_shader_program->isComplited()) return false;

        // TWO BUFFERS
        BufferLayout buffer_layout_2_vec3
        {
            ShaderDataType::Float3,
            ShaderDataType::Float3
        };

        p_vao = std::make_unique<VertexArray>();
        p_positions_colors_vbo = std::make_unique<VertexBuffer>(positions_colors2, sizeof(positions_colors2), buffer_layout_2_vec3);
        p_index_buffer = std::make_unique<IndexBuffer>(indexes, sizeof(indexes) / sizeof(GLuint));
        p_vao->add_vertex_buffer(*p_positions_colors_vbo);
        p_vao->set_index_buffer(*p_index_buffer);

        return 0;
    }
    void Window::shutdown()
    {
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
    }

    void Window::on_update()
    {
        glClearColor(
            m_background_color[0],
            m_background_color[1],
            m_background_color[2],
            m_background_color[3]
        );

        glClear(GL_COLOR_BUFFER_BIT);

        

        p_shader_program->bind();

        // MATH
        // glm::mat4 scale_m(
        //     scale[0], 0, 0, 0,
        //     0, scale[1], 0, 0,
        //     0, 0, scale[2], 0,
        //     0, 0, 0, 1
        // );

        // float rotate_in_radians = glm::radians(rotate);

        // glm::mat4 rotate_m(
        //     glm::cos(rotate_in_radians), glm::sin(rotate_in_radians), 0, 0,
        //     -glm::sin(rotate_in_radians), glm::cos(rotate_in_radians), 0, 0,
        //     0, 0, 1, 0,
        //     0, 0, 0, 1
        // );

        // glm::mat4 translate_m(
        //     1, 0, 0, 0,
        //     0, 1, 0, 0,
        //     0, 0, 1, 0,
        //     translate[0], translate[1], translate[2], 1
        // );

        glm::mat4 rotate_m = glm::mat4(1.f); rotate_m = glm::rotate(rotate_m, glm::radians(rotate), glm::vec3(0.f, 0.f, 1.f));
        glm::mat4 translate_m = glm::mat4(1.f); translate_m = glm::translate(translate_m, translate);
        glm::mat4 scale_m = glm::mat4(1.f); scale_m = glm::scale(scale_m, scale);

        

        

        glm::mat4 model_m = translate_m * rotate_m * scale_m;
        p_shader_program->setMatrix4("model_m", model_m);

        p_vao->bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(p_vao->get_indexes_count()), GL_UNSIGNED_INT, nullptr);

        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize.x = static_cast<float>(get_width());
        io.DisplaySize.y = static_cast<float>(get_height());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        //ImGui::ShowDemoWindow();

        ImGui::Begin("Backgroung color window");
        ImGui::ColorEdit4("Background color", m_background_color);
        ImGui::SliderFloat3("scale", glm::value_ptr(scale), 0.f, 2.f);
        ImGui::SliderFloat("rotate", &rotate, 0.f, 360.f);
        ImGui::SliderFloat3("translate", glm::value_ptr(translate), 0.f, 2.f);

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
    }
}