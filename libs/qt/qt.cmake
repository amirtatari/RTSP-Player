find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_library(ProjectQt INTERFACE)
target_link_libraries(ProjectQt INTERFACE Qt6::Widgets)
