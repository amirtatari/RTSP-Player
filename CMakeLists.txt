cmake_minimum_required(VERSION 3.15)

project(player VERSION 0.1.0)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Modular Dependencies
include(libs/qt/qt.cmake)
include(libs/gst/gstreamer.cmake)

set(PROJECT_SOURCES
    ui/mainwindow.cpp
    ui/mainwindow.ui
    ui/widgets/videoWidget.cpp
    ui/widgets/textBox.cpp
    backend/gstreamer/gstPlayer.cpp
    backend/stateMachine/stateMachine.cpp
    backend/stateMachine/state.cpp
    utils/logger/logger.cpp
)

# Make paths absolute so they can be reused in subdirectories (like tests)
list(TRANSFORM PROJECT_SOURCES PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")

add_executable(${PROJECT_NAME} 
    main.cpp
    ${PROJECT_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ProjectQt
    ProjectGst
)

target_include_directories(${PROJECT_NAME} PRIVATE
    backend/gstreamer
    backend/stateMachine
    ui
    ui/widgets
    utils/logger
)

enable_testing()
add_subdirectory(tests)