cmake_minimum_required(VERSION 3.5)

project(pimu LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Gui REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS OpenGL REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS OpenGLExtensions REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS SerialPort REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS OpenGL REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS OpenGLExtensions REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS SerialPort REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(SOURCES
    cuboid.cpp cuboid.h
    main.cpp
    openglcanvas.cpp openglcanvas.h
    serialparser.cpp serialparser.h
    serialport.cpp serialport.h
    serialportconnection.cpp serialportconnection.h
    serialportreader.cpp serialportreader.h
    window.cpp window.h window.ui
    )
add_executable(pimu ${SOURCES})

target_link_libraries(pimu PRIVATE Qt${QT_VERSION_MAJOR}::Gui)
target_link_libraries(pimu PRIVATE Qt${QT_VERSION_MAJOR}::OpenGL)
target_link_libraries(pimu PRIVATE Qt${QT_VERSION_MAJOR}::OpenGLExtensions)
target_link_libraries(pimu PRIVATE Qt${QT_VERSION_MAJOR}::SerialPort)
target_link_libraries(pimu PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)











#add_qt_executable(pimu
#    GUI
#    SOURCES
#        cuboid.cpp cuboid.h
#        main.cpp
#        openglcanvas.cpp openglcanvas.h
#        serialparser.cpp serialparser.h
#        serialport.cpp serialport.h
#        serialportconnection.cpp serialportconnection.h
#        serialportreader.cpp serialportreader.h
#        window.cpp window.h window.ui
#    PUBLIC_LIBRARIES
#        Qt::Gui
#        Qt::OpenGL
#        Qt::SerialPort
#    ENABLE_AUTOGEN_TOOLS
#        uic
#)

## Resources:
#set(resources_resource_files
#    "shader.frag"
#    "shader.vert"
#)

#add_qt_resource(pimu "resources"
#    PREFIX
#        "/"
#    FILES
#        ${resources_resource_files}
#)


##### Keys ignored in scope 1:.:.:pimu.pro:<TRUE>:
## DISTFILES = "shader.frag" "shader.vert"

### Scopes:
######################################################################

#extend_target(pimu CONDITION (QT_MAJOR_VERSION GREATER 4)
#    PUBLIC_LIBRARIES
#        Qt::Widgets
#)

##### Keys ignored in scope 3:.:.:pimu.pro:QNX:
## target.path = "/tmp/$${TARGET}/bin"

##### Keys ignored in scope 5:.:.:pimu.pro:UNIX AND NOT ANDROID:
## target.path = "/opt/$${TARGET}/bin"

##### Keys ignored in scope 6:.:.:pimu.pro:NOT target.path_ISEMPTY:
## INSTALLS = "target"
