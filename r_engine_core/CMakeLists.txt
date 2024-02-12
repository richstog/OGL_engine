cmake_minimum_required(VERSION 3.12)


set(CORE_PROJECT_NAME r_engine_core)
project(${CORE_PROJECT_NAME})

set(CORE_PUBLIC_INCLUDES
    includes/r_engine_core/Application.hpp
)

set(CORE_PUBLIC_SOURCES
    src/r_engine_core/Application.cpp
)


add_library( ${CORE_PROJECT_NAME} STATIC
    ${CORE_PUBLIC_INCLUDES}
    ${CORE_PUBLIC_SOURCES}
)

target_include_directories(${CORE_PROJECT_NAME} PUBLIC includes)
target_compile_features(${CORE_PROJECT_NAME} PUBLIC cxx_std_17)

# add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
# target_link_libraries(${CORE_PROJECT_NAME} PRIVATE glfw)


include_directories(
        ${GLFW_INCLUDE_DIRS}
)

# add_subdirectory(/usr/lib/x86_64-linux-gnu/cmake/glfw3  ${CMAKE_CURE})
target_link_libraries(${CORE_PROJECT_NAME} PRIVATE glfw)


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${CORE_PROJECT_NAME} ${OPENGL_INCLUDE_DIRS})
target_link_libraries(${CORE_PROJECT_NAME} ${OPENGL_LIBRARIES})