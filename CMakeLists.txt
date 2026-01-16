cmake_minimum_required(VERSION 3.15)

project(player VERSION 0.1.0)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)

# qt6 libs
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# gstreamer libs
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0 gstreamer-video-1.0)

include_directories(
    ${GSTREAMER_INCLUDE_DIRS}
    ${Qt6Widgets_INCLUDE_DIRS}
    backend/gstreamer
    backend/stateMachine
    ui
    ui/widgets
    utils/logger
)

set(PROJECT_SOURCES
    main.cpp
    ui/mainwindow.cpp
    ui/mainwindow.ui
    ui/widgets/videoWidget.cpp
    ui/widgets/textBox.cpp
    backend/gstreamer/gstPlayer.cpp
    backend/stateMachine/stateMachine.cpp
    backend/stateMachine/state.cpp
    utils/logger/logger.cpp
)

add_executable(${PROJECT_NAME} 
    ${PROJECT_SOURCES}
)


target_link_libraries(${PROJECT_NAME}
    ${GSTREAMER_LIBRARIES}
    Qt6::Widgets
)

add_definitions(${GSTREAMER_CFLAGS_OTHER})