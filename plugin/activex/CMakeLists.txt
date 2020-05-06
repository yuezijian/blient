project(activex)

set(BLIENT_ACTIVEX_SOURCE
        main.cpp
        )

if(WIN32)
    list(APPEND BLIENT_ACTIVEX_SOURCE
            AxChannelEditor.hpp
            AxChannelEditor.cpp
            AxChannelReport.hpp
            AxChannelReport.cpp
            AxWidgetEditor.hpp
            AxWidgetEditor.cpp
            AxWidgetReport.hpp
            AxWidgetReport.cpp
            )
else()
    list(APPEND BLIENT_ACTIVEX_SOURCE
            AxWidget.hpp
            AxWidget.cpp
            )
endif()


add_library(activex SHARED ${BLIENT_ACTIVEX_SOURCE})

target_link_libraries(activex ${QT_LIBRARIES})
