#include <iostream>
#include <memory>

#include <r_engine_core/Application.hpp>
#include <r_engine_core/Log.hpp>
#include <r_engine_core/Input.hpp>
#include <r_engine_core/Camera.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

//#define NON_INTERFACE

class R_Engine_Editor : public r_engine::Application {

    double m_initial_mouse_pos_x = 0.0;
    double m_initial_mouse_pos_y = 0.0;

    float camera_position[3] = {0.f, 0.f, 1.f};
    float camera_rotation[3] = {0.f, 0.f, 0.f};
    float camera_fov = 60.f;
    float camera_near_plane = 0.1f;
    float camera_far_plane = 100.f;
    bool camera_perspective = true;

    virtual void on_update() override
    {
        glm::vec3 movement_delta {0, 0, 0};
        glm::vec3 rotation_delta {0, 0, 0};

        // Camera position
        if (r_engine::Input::IsKeyPressed(r_engine::KeyCode::KEY_W))
        {
            movement_delta.x += 0.05f;
        }
        if (r_engine::Input::IsKeyPressed(r_engine::KeyCode::KEY_S))
        {
            movement_delta.x -= 0.05f;
        }

        if (r_engine::Input::IsKeyPressed(r_engine::KeyCode::KEY_A))
        {
            movement_delta.y -= 0.05f;
        }
        if (r_engine::Input::IsKeyPressed(r_engine::KeyCode::KEY_D))
        {
            movement_delta.y += 0.05f;
        }

        if (r_engine::Input::IsKeyPressed(r_engine::KeyCode::KEY_E))
        {
            movement_delta.z += 0.05f;
        }
        if (r_engine::Input::IsKeyPressed(r_engine::KeyCode::KEY_Q))
        {
            movement_delta.z -= 0.05f;
        }

        // Camera rotation
        if (r_engine::Input::IsKeyPressed(r_engine::KeyCode::KEY_UP))
        {
            rotation_delta.y -= 0.5f;
        }
        if (r_engine::Input::IsKeyPressed(r_engine::KeyCode::KEY_DOWN))
        {
            rotation_delta.y += 0.5f;
        }
        if (r_engine::Input::IsKeyPressed(r_engine::KeyCode::KEY_LEFT))
        {
            rotation_delta.z += 0.5f;
        }
        if (r_engine::Input::IsKeyPressed(r_engine::KeyCode::KEY_RIGHT))
        {
            rotation_delta.z -= 0.5f;
        }
        if (r_engine::Input::IsKeyPressed(r_engine::KeyCode::KEY_P))
        {
            rotation_delta.x += 0.5f;
        }
        if (r_engine::Input::IsKeyPressed(r_engine::KeyCode::KEY_O))
        {
            rotation_delta.x -= 0.5f;
        }

        if (r_engine::Input::isMouseButtonPressed(r_engine::MouseButtonCode::MOUSE_BUTTON_RIGHT))
        {
            glm::vec2 current_cursor_position = get_current_cursor_position();
            if (r_engine::Input::isMouseButtonPressed(r_engine::MouseButtonCode::MOUSE_BUTTON_LEFT))
            {
                camera.move_right(static_cast<float>((current_cursor_position.x - m_initial_mouse_pos_x) / 100.f));
                camera.move_up(static_cast<float>((m_initial_mouse_pos_y - current_cursor_position.y) / 100.f));
            } else
            {
                rotation_delta.z += static_cast<float>((m_initial_mouse_pos_x - current_cursor_position.x) / 5.f);
                rotation_delta.y -= static_cast<float>((m_initial_mouse_pos_y - current_cursor_position.y) / 5.f);
            }

            m_initial_mouse_pos_x = current_cursor_position.x;
            m_initial_mouse_pos_y = current_cursor_position.y;
        }

        camera.add_movement_and_rotation(movement_delta, rotation_delta);
    }

    void setup_dockspace_menu()
    {
        /* Dockspace flags */
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_NoWindowMenuButton;
        dockspace_flags |= ImGuiDockNodeFlags_PassthruCentralNode;

        /* Window flags */
        static ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        window_flags |= ImGuiWindowFlags_NoBackground;

        /* Opt fullscreen */
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

        /* Opt padding */
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Dockspace", nullptr, window_flags);
        ImGui::PopStyleVar(3);

        /* Create dockspace */
        ImGuiIO& io = ImGui::GetIO();
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New scene...", NULL))
                {

                }

                if (ImGui::MenuItem("Open scene...", NULL))
                {

                }

                if (ImGui::MenuItem("Save scene...", NULL))
                {

                }

                ImGui::Separator();

                if (ImGui::MenuItem("Exit", NULL))
                {
                    close();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        ImGui::End();
    }

    virtual void on_mouse_button_pressed_event(const r_engine::MouseButtonCode button_code, const double x_pos, const double y_pos, const bool pressed) override
    {
        m_initial_mouse_pos_x = x_pos;
        m_initial_mouse_pos_y = y_pos;
    }

    virtual void on_ui_draw() override
    {
        setup_dockspace_menu();

        camera_position[0] = camera.get_position().x;
        camera_position[1] = camera.get_position().y;
        camera_position[2] = camera.get_position().z;

        camera_rotation[0] = camera.get_rotation().x;
        camera_rotation[1] = camera.get_rotation().y;
        camera_rotation[2] = camera.get_rotation().z;

        camera_fov = camera.get_field_of_view();
        camera_far_plane = camera.get_far_clip_plane();
        camera_near_plane = camera.get_near_clip_plane();

        ImGui::Begin("Editor");

        /* LIGHT UI */
        ImGui::SliderFloat3("Light position", light_position, -10.f, 10.f);
        ImGui::ColorEdit3("Light color", light_color);
        ImGui::SliderFloat("Light ambient factor", &light_ambient_factor, 0.f, 1.f);
        ImGui::SliderFloat("Light diffuse factor", &light_diffuse_factor, 0.f, 1.f);
        ImGui::SliderFloat("Light specular factor", &light_specular_factor, 0.f, 1.f);
        ImGui::SliderFloat("Light shininess", &light_shininess, 1.f, 128.f);

        /* CAMERA UI */
        if (ImGui::SliderFloat3("Camera position", camera_position, -10.f, 10.f))
        {
            camera.set_position(glm::vec3(camera_position[0], camera_position[1], camera_position[2]));
        }
        if (ImGui::SliderFloat3("Camera rotation", camera_rotation, 0.f, 360.f))
        {
            camera.set_rotation(glm::vec3(camera_rotation[0], camera_rotation[1], camera_rotation[2]));
        }
        if (ImGui::SliderFloat("Camera FOV", &camera_fov, 1.f, 120.f))
        {
            camera.set_field_of_view(camera_fov);
        }
        if (ImGui::SliderFloat("Camera near clip plane", &camera_near_plane, 0.1f, 10.f))
        {
            camera.set_near_clip_plane(camera_near_plane);
        }
        if (ImGui::SliderFloat("Camera far clip plane", &camera_far_plane, 1.f, 100.f))
        {
            camera.set_far_clip_plane(camera_far_plane);
        }
        if (ImGui::Checkbox("Camera perspective", &camera_perspective))
        {
            camera.set_projection_mode(
                camera_perspective ?
                r_engine::Camera::ProjectionMode::Perspective : r_engine::Camera::ProjectionMode::Orthographic
            );
        }
        ImGui::End();
    }

    int frame = 0;
};

int main()
{
    std::unique_ptr r_engine_editor = std::make_unique<R_Engine_Editor>();

    int returnCode = r_engine_editor->start(1024, 768, "R Engine Editor");

    return returnCode;
}