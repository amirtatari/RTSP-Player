find_package(Qt6 COMPONENTS Test REQUIRED)

add_executable(unit_tests 
    tst_main.cpp
    ${PROJECT_SOURCES}
)

target_link_libraries(unit_tests PRIVATE
    Qt6::Test
    Qt6::Widgets
    ProjectQt
    ProjectGst
)

target_include_directories(unit_tests PRIVATE
    ../backend/gstreamer
    ../backend/stateMachine
    ../ui
    ../ui/widgets
    ../utils/logger
)

add_test(NAME AllTests COMMAND unit_tests)
