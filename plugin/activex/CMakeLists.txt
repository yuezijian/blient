project(activex)

set(BLIENT_ACTIVEX_SOURCE
        main.cpp
        WebEngineChannelObject.hpp
        WebEngineChannelObject.cpp
        )

add_library(activex SHARED ${BLIENT_ACTIVEX_SOURCE})

target_link_libraries(activex ${QT_LIBRARIES})
