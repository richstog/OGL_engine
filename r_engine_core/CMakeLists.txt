cmake_minimum_required(VERSION 3.12)


set(CORE_PROJECT_NAME r_engine_core)
project(${CORE_PROJECT_NAME})

# PUBLIC INCLUDES
set(CORE_PUBLIC_INCLUDES
    includes/r_engine_core/Application.hpp
    includes/r_engine_core/Log.hpp
    includes/r_engine_core/Event.hpp
)

# PRIVATE INCLUDES
set(CORE_PRIVATE_INCLUDES
    src/r_engine_core/Window.hpp
)

# PRIVATE SOURCES
set(CORE_PRIVATE_SOURCES
    src/r_engine_core/Application.cpp
    src/r_engine_core/Window.cpp
)


add_library( ${CORE_PROJECT_NAME} STATIC
    ${CORE_PUBLIC_INCLUDES}
    ${CORE_PRIVATE_INCLUDES}
    ${CORE_PRIVATE_SOURCES}
)

target_include_directories(${CORE_PROJECT_NAME} PUBLIC includes)
target_include_directories(${CORE_PROJECT_NAME} PRIVATE src)

target_compile_features(${CORE_PROJECT_NAME} PUBLIC cxx_std_17)

# OGL, GLFW LINK
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(${CORE_PROJECT_NAME} PRIVATE glfw OpenGL::GL)

# SPDLOG LINK
add_subdirectory(../external/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)
target_link_libraries(${CORE_PROJECT_NAME} PRIVATE spdlog)

# IMGUI LINK
set(IMGUI_INCLUDES
    ../external/imgui/imgui.h
    ../external/imgui/backends/imgui_impl_glfw.h
    ../external/imgui/backends/imgui_impl_opengl3.h
)

set(IMGUI_SOURCES
    ../external/imgui/imgui.cpp
    ../external/imgui/backends/imgui_impl_glfw.cpp
    ../external/imgui/backends/imgui_impl_opengl3.cpp
    ../external/imgui/imgui_demo.cpp
    ../external/imgui/imgui_draw.cpp
    ../external/imgui/imgui_tables.cpp
    ../external/imgui/imgui_widgets.cpp
)

add_library( ImGUI STATIC
    ${IMGUI_INCLUDES}
    ${IMGUI_SOURCES}
)

target_include_directories(ImGUI PUBLIC ../external)
target_include_directories(ImGUI PUBLIC ../external/imgui)

target_link_libraries(ImGUI PRIVATE glfw OpenGL::GL)
target_link_libraries(${CORE_PROJECT_NAME} PRIVATE ImGUI)