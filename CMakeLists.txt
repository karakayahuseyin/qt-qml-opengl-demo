cmake_minimum_required(VERSION 3.16)

project(opengl-qt-1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick OpenGL)

qt_add_executable(opengl-qt-1
    src/main.cpp
    Qml.qrc 
)

qt_add_qml_module(opengl-qt-1
    URI QmlOpenGL
    VERSION 1.0
    QML_FILES
        Qml.qrc
)

add_subdirectory(src/OpenGLRenderer)

target_link_libraries(opengl-qt-1 PUBLIC
    Qt6::Quick
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::OpenGL
    OpenGLRenderer
)
