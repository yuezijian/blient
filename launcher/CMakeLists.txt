project(launcher)

set(BLIENT_LAUNCHER_SOURCE
        main.cpp
        )

add_executable(launcher ${BLIENT_LAUNCHER_SOURCE})

set_property(TARGET launcher PROPERTY WIN32_EXECUTABLE TRUE)

target_link_libraries(launcher ${QT_LIBRARIES})
