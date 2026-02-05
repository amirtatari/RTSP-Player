find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0 gstreamer-video-1.0 x11)

add_library(ProjectGst INTERFACE)

target_include_directories(ProjectGst INTERFACE ${GSTREAMER_INCLUDE_DIRS})
target_link_libraries(ProjectGst INTERFACE ${GSTREAMER_LIBRARIES})
target_compile_options(ProjectGst INTERFACE ${GSTREAMER_CFLAGS_OTHER})
