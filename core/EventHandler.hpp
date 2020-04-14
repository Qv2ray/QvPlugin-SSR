#pragma once
#include "QvPluginProcessor.hpp"

class SSRPluginEventHandler : public Qv2rayPlugin::QvPluginEventHandler
{
  public:
    SSRPluginEventHandler(QObject *parent = nullptr);
    // SSR Plugin does not receive any events.
};
