#pragma once

#include "QvPluginProcessor.hpp"
#include "common/CommonHelpers.hpp"

#include <QList>
namespace SSRPlugin
{
    QJsonObject GenerateShadowSocksROUT(QList<ShadowSocksRServerObject> servers);
    class SSRSerializer : public Qv2rayPlugin::QvPluginSerializer
    {
        Q_OBJECT
      public:
        explicit SSRSerializer(QObject *parent = nullptr) : Qv2rayPlugin::QvPluginSerializer(parent){};
        const QString SerializeOutbound(const QString &protocol,  //
                                        const QString &alias,     //
                                        const QString &groupName, //
                                        const QJsonObject &object) const override;
        const QPair<QString, QJsonObject> DeserializeOutbound(const QString &link, QString *alias, QString *errorMessage) const override;
        const Qv2rayPlugin::QvPluginOutboundInfoObject GetOutboundInfo(const QString &protocol, const QJsonObject &outbound) const override
        {
            if (protocol == "shadowsocksr")
            {
                auto r = ShadowSocksRServerObject::fromJson(outbound);
                return Qv2rayPlugin::QvPluginOutboundInfoObject{ r.address, "shadowsocksr", r.port };
            }
            else
            {
                return {};
            }
        }
        const QList<QString> ShareLinkPrefixes() const override
        {
            return { "ssr://" };
        };
        const QList<QString> OutboundProtocols() const override
        {
            return { "shadowsocksr" };
        }
    };
}; // namespace SSRPlugin
