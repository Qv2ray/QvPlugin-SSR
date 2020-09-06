#include "SSRPlugin.hpp"

#include "core/Serializer.hpp"
#include "ui/GUIInterface.hpp"

#include <QDateTime>

namespace SSRPlugin
{
    bool QvSSRPlugin::InitializePlugin(const QString &, const QJsonObject &)
    {
        emit PluginLog("Initialize plugin.");
        eventHandler = std::make_shared<SSRPluginEventHandler>();
        outboundHandler = std::make_shared<SSRSerializer>();
        kernelInterface = std::make_unique<SSRKernelInterface>();
        guiInterface = new SSRGuiInterface();
        return true;
    }
} // namespace SSRPlugin
