project(QvSSRPlugin)
cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 14)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Widgets Gui Network REQUIRED)

set(QVPLUGIN_INTERFACE_INCLUDE_DIR "interface/")
include(cmake/shadowsocksr-uvw.cmake)
include(interface/QvPluginInterface.cmake)
include_directories(${QVPLUGIN_INTERFACE_INCLUDE_DIR})

add_library(${PROJECT_NAME} MODULE
    SimplePlugin.hpp
    SimplePlugin.cpp
    common/CommonHelpers.cpp
    common/CommonHelpers.hpp
    converter/ShareLinkParser.cpp
    converter/ShareLinkParser.hpp
    SimplePluginEventHandler.cpp
    SimplePluginEventHandler.hpp
    kernel/httpProxy.cpp
    kernel/httpProxy.hpp
    kernel/socketStream.cpp
    kernel/socketStream.hpp
    kernel/SSRInstance.cpp
    kernel/SSRInstance.hpp
    resx.qrc
    ${QVPLUGIN_INTERFACE_HEADERS})
    
if(APPLE)
    add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_INSTALL_NAME_TOOL} -add_rpath "@executable_path/../../Frameworks/" $<TARGET_FILE:${PROJECT_NAME}>)
endif()

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Network
    ${SHADOWSOCKSR_UVW_LIBRARY})
