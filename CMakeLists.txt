cmake_minimum_required(VERSION 3.15)

project(blient)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/../_build")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/../_build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/../_build")

#option(USE_PLUGIN_ACTIVEX "Build the ActiveX plugin for Windows" OFF)

if(MSVC)
    add_compile_options(/wd4819)
endif()

set(QT_PACKAGES Core Gui WebEngineWidgets Widgets)
set(QT_LIBRARIES Qt5::Core Qt5::Gui Qt5::WebEngineWidgets Qt5::Widgets)

#if(WIN32 AND USE_PLUGIN_ACTIVEX)
if(WIN32)
    list(APPEND QT_PACKAGES AxContainer)
    list(APPEND QT_LIBRARIES Qt5::AxContainer)
endif()

find_package(Qt5 CONFIG REQUIRED ${QT_PACKAGES})

add_subdirectory(client)
add_subdirectory(launcher)
add_subdirectory(plugin/activex)

#if(WIN32 AND USE_PLUGIN_ACTIVEX)
#    list(APPEND BLIENT_LAUNCHER_DEPENDENCIES activex)
#endif()

set(BLIENT_LAUNCHER_DEPENDENCIES client activex)

add_dependencies(launcher ${BLIENT_LAUNCHER_DEPENDENCIES})
