#pragma once

#include "QvPluginInterface.hpp"
#include "SimplePluginEventHandler.hpp"
#include "SimplePluginKernel.hpp"

#include <QObject>
#include <QtPlugin>

class QLabel;
using namespace Qv2rayPlugin;

class SimplePlugin
    : public QObject
    , Qv2rayInterface
{
    Q_INTERFACES(Qv2rayPlugin::Qv2rayInterface)
    Q_PLUGIN_METADATA(IID Qv2rayInterface_IID)
    Q_OBJECT
  public:
    //
    // Basic metainfo of this plugin
    const QvPluginMetadata GetMetadata() const override
    {
        return QvPluginMetadata{
            "Example Plugin",                                 //
            "Example Author",                                 //
            "qvplugin_test",                                  //
            "QvSimplePlugin is a simple plugin for testing.", //
            QIcon(":/qv2ray.png"),                            //
            { CAPABILITY_CONNECTION_ENTRY,                    //
              CAPABILITY_CONNECTIVITY,                        //
              CAPABILITY_STATS,                               //
              CAPABILITY_SYSTEM_PROXY },                      //
            { SPECIAL_TYPE_KERNEL,                            //
              SPECIAL_TYPE_SERIALIZOR }                       //
        };
    }
    //
    QWidget *GetSettingsWidget() override;
    QvPluginEditor *GetEditorWidget(UI_TYPE) override;
    QvPluginKernel *GetKernel() override;
    //
    bool UpdateSettings(const QJsonObject &) override;
    bool Initialize(const QString &, const QJsonObject &) override;
    const QJsonObject GetSettngs() override;
    //
    QvPluginEventHandler *GetEventHandler() override;
  signals:
    void PluginLog(const QString &) const override;
    void PluginErrorMessageBox(const QString &) const override;

  private:
    QJsonObject settings;
    QLabel *pluginWidget;
    SimplePluginEventHandler *eventHandler;
    SimplePluginKernel *kernel;
};
