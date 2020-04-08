#include "SimplePlugin.hpp"

#include <QDateTime>
#include <QLabel>
#include <QMetaEnum>
namespace SSRPlugin
{
    QvPluginKernel *QvSSRPlugin::GetKernel()
    {
        return kernel;
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
        eventHandler = new SimplePluginEventHandler(this);
        kernel = new ShadowsocksrInstance(this);
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
            case UI_TYPE_OUTBOUND_EDITOR:
            case UI_TYPE_GROUP_EDITOR: break;
        }
        return nullptr;
    }
} // namespace SSRPlugin
