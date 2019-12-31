project(activex)

add_library(activex SHARED main.cpp WebEngineChannelObject.cpp)

target_link_libraries(activex ${QT_LIBRARIES})
