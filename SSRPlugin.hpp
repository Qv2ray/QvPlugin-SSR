#pragma once

#include "QvPluginInterface.hpp"
#include "core/EventHandler.hpp"
#include "core/Serializer.hpp"
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
                "v3.0.0",                             //
                "Qv2ray/QvPlugin-SSR",                //
                {
                    COMPONENT_GUI,             //
                    COMPONENT_KERNEL,          //
                    COMPONENT_OUTBOUND_HANDLER //
                },
                UPDATE_GITHUB_RELEASE //
            };
        }
        bool InitializePlugin(const QString &, const QJsonObject &) override;
        //
      signals:
        void PluginLog(const QString &) const override;
        void PluginErrorMessageBox(const QString &, const QString &) const override;

      private:
        QJsonObject settings;
    };
} // namespace SSRPlugin
