#include "SimplePlugin.hpp"

#include <QDateTime>
#include <QLabel>
#include <QMetaEnum>

QvPluginKernel *SimplePlugin::GetKernel()
{
    return kernel;
}

bool SimplePlugin::UpdateSettings(const QJsonObject &conf)
{
    settings = conf;
    return true;
}

bool SimplePlugin::Initialize(const QString &, const QJsonObject &settings)
{
    emit PluginLog("Initialize plugin.");
    this->settings = settings;
    pluginWidget = new QLabel;
    eventHandler = new SimplePluginEventHandler(this);
    kernel = new SimplePluginKernel(this);
    return true;
}

const QJsonObject SimplePlugin::GetSettngs()
{
    emit PluginLog("Getting plugin settings.");
    return settings;
}

QvPluginEventHandler *SimplePlugin::GetEventHandler()
{
    return eventHandler;
}

QWidget *SimplePlugin::GetSettingsWidget()
{
    pluginWidget->setText("From Settings: " + settings["msg"].toString());
    return pluginWidget;
}

QvPluginEditor *SimplePlugin::GetEditorWidget(UI_TYPE type)
{
    switch (type)
    {
        case UI_TYPE_INBOUND_EDITOR:
        case UI_TYPE_OUTBOUND_EDITOR:
        case UI_TYPE_GROUP_EDITOR: break;
    }
    return nullptr;
}
