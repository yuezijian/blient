project(client VERSION 0.0.1)

configure_file(ClientConfig.h.in ClientConfig.hpp)

set(BLIENT_CLIENT_SOURCE
        _client.hpp
        _client.cpp
        Client.hpp
        Client.cpp
        TabWidget.hpp
        TabWidget.cpp
        MainWindow.hpp
        MainWindow.cpp
        WebEngineConsole.hpp
        WebEngineConsole.cpp
        WebEnginePage.hpp
        WebEnginePage.cpp
        WebEngineView.hpp
        WebEngineView.cpp
        )

add_library(client SHARED ${BLIENT_CLIENT_SOURCE} ../resource/resource.qrc)

target_include_directories(client PRIVATE ${PROJECT_BINARY_DIR})

target_link_libraries(client ${QT_LIBRARIES})
