project(launcher)

set(BLIENT_LAUNCHER_SOURCE
        main.cpp
        )

add_executable(launcher ${BLIENT_LAUNCHER_SOURCE})

target_link_libraries(launcher ${QT_LIBRARIES})
