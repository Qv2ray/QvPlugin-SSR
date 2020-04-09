#pragma once

#include "QvPluginInterface.hpp"
#include "core/EventHandler.hpp"
#include "core/kernel/SSRInstance.hpp"

#include <QObject>
#include <QtPlugin>

class QLabel;
using namespace Qv2rayPlugin;
namespace SSRPlugin
{
    class QvSSRPlugin
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
                "SSR Plugin",                         //
                "Qv2ray Development Group",           //
                "qvplugin_ssr",                       //
                "Support SSR connections in Qv2ray.", //
                QIcon(":/qv2ray.png"),                //
                { CAPABILITY_CONNECTION_ENTRY,        //
                  CAPABILITY_CONNECTIVITY,            //
                  CAPABILITY_STATS,                   //
                  CAPABILITY_SYSTEM_PROXY },          //
                { SPECIAL_TYPE_KERNEL,                //
                  SPECIAL_TYPE_SERIALIZOR }           //
            };
        }
        //
        QWidget *GetSettingsWidget() override;
        QvPluginEditor *GetEditorWidget(UI_TYPE) override;
        QvPluginKernel *GetKernel() override;
        QvPluginSerializer *GetSerializer() override;
        QvPluginEventHandler *GetEventHandler() override;
        //
        bool UpdateSettings(const QJsonObject &) override;
        bool Initialize(const QString &, const QJsonObject &) override;
        const QJsonObject GetSettngs() override;
        //
      signals:
        void PluginLog(const QString &) const override;
        void PluginErrorMessageBox(const QString &) const override;

      private:
        QJsonObject settings;
        QLabel *pluginWidget;
        SSRPluginEventHandler *eventHandler;
        QvPluginSerializer *serializer;
        SSRKernelInstance *kernel;
    };
} // namespace SSRPlugin
