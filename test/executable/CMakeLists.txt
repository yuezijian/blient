project(test_executable)

set(BLIENT_TEST_EXECUTABLE_SOURCE
        main.cpp
        )

add_executable(test_executable ${BLIENT_TEST_EXECUTABLE_SOURCE})

set_property(TARGET test_executable PROPERTY WIN32_EXECUTABLE TRUE)

target_link_libraries(test_executable ${QT_LIBRARIES})
