QT += core gui widgets
CONFIG += qt c++11 plugin

TEMPLATE = lib

include(interface/QvPluginInterface.pri)

SOURCES += SimplePlugin.cpp SimplePluginKernel.cpp SimplePluginEventHandler.cpp
HEADERS += SimplePlugin.hpp SimplePluginKernel.hpp SimplePluginEventHandler.hpp
RESOURCES += resx.qrc
