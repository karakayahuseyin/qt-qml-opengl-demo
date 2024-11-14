cmake_minimum_required(VERSION 3.16)

find_package(Qt6 REQUIRED COMPONENTS Core)

qt_add_library(OpenGLRenderer STATIC
    opengl_item.cpp
    opengl_item.hpp
    opengl_renderer.hpp
    opengl_renderer.cpp
)

qt_standard_project_setup()

target_link_libraries(OpenGLRenderer PUBLIC
    Qt6::Quick
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
)

set_target_properties(OpenGLRenderer PROPERTIES
    AUTOMOC ON
)

target_include_directories(OpenGLRenderer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
