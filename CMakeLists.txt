cmake_minimum_required(VERSION 3.15)

project(blient)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if(MSVC)
    add_compile_options(/wd4819)
endif()

set(QT_PACKAGES Core Gui WebEngineWidgets Widgets)
set(QT_LIBRARIES Qt5::Core Qt5::Gui Qt5::WebEngineWidgets Qt5::Widgets)

if(WIN32)
    list(APPEND QT_PACKAGES AxContainer)
    list(APPEND QT_LIBRARIES Qt5::AxContainer)
endif()

find_package(Qt5 CONFIG REQUIRED ${QT_PACKAGES})

if(WIN32)
    add_subdirectory(activex)
endif()

add_subdirectory(client)
