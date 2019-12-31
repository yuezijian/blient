project(client)

add_executable(client
        main.cpp
        MainWindow.cpp
        WebEnginePage.cpp
        )

target_link_libraries(client ${QT_LIBRARIES})
