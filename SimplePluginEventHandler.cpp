#include "SimplePluginEventHandler.hpp"

SimplePluginEventHandler::SimplePluginEventHandler(QObject *parent) : Qv2rayPlugin::QvPluginEventHandler(parent)
{
}

void SimplePluginEventHandler::ProcessEvent_Connectivity(const ::Qv2rayPlugin::QvConnectivityEventObject &)
{
}

void SimplePluginEventHandler::ProcessEvent_SystemProxy(const ::Qv2rayPlugin::QvSystemProxyEventObject &)
{
}

void SimplePluginEventHandler::ProcessEvent_ConnectionEntry(const ::Qv2rayPlugin::QvConnectionEntryEventObject &)
{
}

void SimplePluginEventHandler::ProcessEvent_ConnectionStats(const ::Qv2rayPlugin::QvConnectionStatsEventObject &)
{
}
