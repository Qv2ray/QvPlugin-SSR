#pragma once
#include "QvPluginProcessor.hpp"

class SSRPluginEventHandler : public Qv2rayPlugin::PluginEventHandler
{
  public:
    SSRPluginEventHandler();
    // SSR Plugin does not receive any events.
};
