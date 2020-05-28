#include "SSRPlugin.hpp"

#include "core/Serializer.hpp"
#include "ui/SSROutboundEditor.hpp"

#include <QDateTime>
#include <QLabel>
#include <QMetaEnum>
namespace SSRPlugin
{
    std::unique_ptr<QvPluginKernel> QvSSRPlugin::CreateKernel()
    {
        return std::make_unique<SSRKernelInstance>();
    }

    std::shared_ptr<QvPluginSerializer> QvSSRPlugin::GetSerializer()
    {
        return serializer;
    }

    bool QvSSRPlugin::UpdateSettings(const QJsonObject &conf)
    {
        settings = conf;
        return true;
    }

    bool QvSSRPlugin::Initialize(const QString &, const QJsonObject &settings)
    {
        emit PluginLog("Initialize plugin.");
        this->settings = settings;
        eventHandler = std::make_shared<SSRPluginEventHandler>(this);
        serializer = std::make_shared<SSRSerializer>(this);
        return true;
    }

    const QJsonObject QvSSRPlugin::GetSettngs()
    {
        emit PluginLog("Getting plugin settings.");
        return settings;
    }

    std::shared_ptr<QvPluginEventHandler> QvSSRPlugin::GetEventHandler()
    {
        return eventHandler;
    }

    std::unique_ptr<QWidget> QvSSRPlugin::GetSettingsWidget()
    {
        return nullptr;
    }

    std::unique_ptr<QvPluginEditor> QvSSRPlugin::GetEditorWidget(UI_TYPE type)
    {
        switch (type)
        {
            case UI_TYPE_INBOUND_EDITOR:
            case UI_TYPE_GROUP_EDITOR: break;
            case UI_TYPE_OUTBOUND_EDITOR:
            {
                return std::make_unique<SSROutboundEditor>();
            }
        }
        return nullptr;
    }
} // namespace SSRPlugin
