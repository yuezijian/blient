project(client VERSION 0.0.1)

configure_file(ClientConfig.h.in ClientConfig.hpp)

set(BLIENT_CLIENT_SOURCE
        _client.hpp
        _client.cpp
        Client.hpp
        Client.cpp
        MainWindow.hpp
        MainWindow.cpp
        TabWidget.hpp
        TabWidget.cpp
        WebWidget.hpp
        WebWidget.cpp
        engine/WebEnginePage.hpp
        engine/WebEnginePage.cpp
        engine/WebEngineUrlSchemeHandlerExecutable.hpp
        engine/WebEngineUrlSchemeHandlerExecutable.cpp
        engine/WebEngineView.hpp
        engine/WebEngineView.cpp
        engine/auxiliary/ChannelObject.hpp
        engine/auxiliary/ChannelObject.cpp
        engine/auxiliary/ConsoleWidget.hpp
        engine/auxiliary/ConsoleWidget.cpp
        engine/auxiliary/PopupWidget.hpp
        engine/auxiliary/PopupWidget.cpp
        )

add_library(client SHARED ${BLIENT_CLIENT_SOURCE} ../resource/resource.qrc)

target_include_directories(client PRIVATE ${PROJECT_BINARY_DIR})

target_link_libraries(client ${QT_LIBRARIES})
