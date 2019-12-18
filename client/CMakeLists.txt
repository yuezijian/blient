project(client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 CONFIG REQUIRED Core Gui WebEngineWidgets Widgets)

add_executable(client
        main.cpp
        MainWindow.cpp
        )

target_link_libraries(client Qt5::Core Qt5::Gui Qt5::WebEngineWidgets Qt5::Widgets)
