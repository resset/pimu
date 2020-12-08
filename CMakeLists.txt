cmake_minimum_required(VERSION 3.5)

project(pimu LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_LIBRARIES Gui OpenGL OpenGLExtensions SerialPort Widgets)

find_package(QT NAMES Qt6 Qt5 COMPONENTS ${QT_LIBRARIES} REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS ${QT_LIBRARIES} REQUIRED)

qt_add_resources(SHADERS_RES shaders.qrc)

set(SOURCES
    cuboid.cpp cuboid.h
    main.cpp
    openglcanvas.cpp openglcanvas.h
    serialparser.cpp serialparser.h
    serialport.cpp serialport.h
    serialportconnection.cpp serialportconnection.h
    serialportreader.cpp serialportreader.h
    window.cpp window.h
)
add_executable(pimu ${SOURCES} ${SHADERS_RES})

target_link_libraries(pimu
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::OpenGL
    Qt${QT_VERSION_MAJOR}::OpenGLExtensions
    Qt${QT_VERSION_MAJOR}::SerialPort
    Qt${QT_VERSION_MAJOR}::Widgets
)
