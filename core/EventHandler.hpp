#pragma once
#include "Qv2rayPluginProcessor.hpp"

class SSRPluginEventHandler : public Qv2rayPlugin::QvPluginEventHandler
{
  public:
    SSRPluginEventHandler(QObject *parent = nullptr);
    QVPlUGIN_DECL_EVENT_HANDLER_OVERRIDE(SystemProxy);
    QVPlUGIN_DECL_EVENT_HANDLER_OVERRIDE(Connectivity);
    QVPlUGIN_DECL_EVENT_HANDLER_OVERRIDE(ConnectionStats);
    QVPlUGIN_DECL_EVENT_HANDLER_OVERRIDE(ConnectionEntry);
};
