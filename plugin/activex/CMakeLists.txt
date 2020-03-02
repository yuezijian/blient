project(activex)

set(BLIENT_ACTIVEX_SOURCE
        main.cpp
        WebEngineChannelObject.hpp
        WebEngineChannelObject.cpp
        )

if(WIN32)
    list(APPEND BLIENT_ACTIVEX_SOURCE AxWidgetEditor.hpp AxWidgetEditor.cpp)
else()
    list(APPEND BLIENT_ACTIVEX_SOURCE AxWidget.hpp)
endif()


add_library(activex SHARED ${BLIENT_ACTIVEX_SOURCE})

target_link_libraries(activex ${QT_LIBRARIES})
