#include "EventHandler.hpp"

SSRPluginEventHandler::SSRPluginEventHandler(QObject *parent) : Qv2rayPlugin::QvPluginEventHandler(parent)
{
}

void SSRPluginEventHandler::ProcessEvent_Connectivity(const ::Qv2rayPlugin::QvConnectivityEventObject &)
{
}

void SSRPluginEventHandler::ProcessEvent_SystemProxy(const ::Qv2rayPlugin::QvSystemProxyEventObject &)
{
}

void SSRPluginEventHandler::ProcessEvent_ConnectionEntry(const ::Qv2rayPlugin::QvConnectionEntryEventObject &)
{
}

void SSRPluginEventHandler::ProcessEvent_ConnectionStats(const ::Qv2rayPlugin::QvConnectionStatsEventObject &)
{
}
