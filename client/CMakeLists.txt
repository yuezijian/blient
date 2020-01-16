project(client VERSION 0.0.1)

set(BLIENT_CLIENT_SOURCE
        _client.hpp
        _client.cpp
        Client.hpp
        Client.cpp
        MainWindow.hpp
        MainWindow.cpp
        WebEnginePage.hpp
        WebEnginePage.cpp
        WebEngineView.hpp
        WebEngineView.cpp
        )

add_library(client SHARED ${BLIENT_CLIENT_SOURCE})

target_link_libraries(client ${QT_LIBRARIES})
