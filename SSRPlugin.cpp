#include "SSRPlugin.hpp"

#include "core/Serializer.hpp"
#include "ui/SSROutboundEditor.hpp"

#include <QDateTime>
#include <QLabel>
#include <QMetaEnum>
namespace SSRPlugin
{
    QvPluginKernel *QvSSRPlugin::GetKernel()
    {
        return kernel;
    }

    QvPluginSerializer *QvSSRPlugin::GetSerializer()
    {
        return nullptr;
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
        pluginWidget = new QLabel;
        eventHandler = new SSRPluginEventHandler(this);
        kernel = new SSRKernelInstance(this);
        serializer = new SSRSerializer(this);
        return true;
    }

    const QJsonObject QvSSRPlugin::GetSettngs()
    {
        emit PluginLog("Getting plugin settings.");
        return settings;
    }

    QvPluginEventHandler *QvSSRPlugin::GetEventHandler()
    {
        return eventHandler;
    }

    QWidget *QvSSRPlugin::GetSettingsWidget()
    {
        pluginWidget->setText("From Settings: " + settings["msg"].toString());
        return pluginWidget;
    }

    QvPluginEditor *QvSSRPlugin::GetEditorWidget(UI_TYPE type)
    {
        switch (type)
        {
            case UI_TYPE_INBOUND_EDITOR:
            case UI_TYPE_GROUP_EDITOR: break;
            case UI_TYPE_OUTBOUND_EDITOR:
            {
                return new SSROutboundEditor();
            }
        }
        return nullptr;
    }
} // namespace SSRPlugin
