#pragma once

#include "QvPluginProcessor.hpp"
#include "common/CommonHelpers.hpp"

#include <QList>
using namespace Qv2rayPlugin;
namespace SSRPlugin
{
    QJsonObject GenerateShadowSocksROUT(QList<ShadowSocksRServerObject> servers);
    class SSRSerializer : public Qv2rayPlugin::PluginOutboundHandler
    {
      public:
        explicit SSRSerializer() : PluginOutboundHandler(){};
        const QString SerializeOutbound(const QString &protocol,  //
                                        const QString &alias,     //
                                        const QString &groupName, //
                                        const QJsonObject &object) const override;
        const QPair<QString, QJsonObject> DeserializeOutbound(const QString &link, QString *alias, QString *errorMessage) const override;
        const Qv2rayPlugin::OutboundInfoObject GetOutboundInfo(const QString &protocol, const QJsonObject &outbound) const override
        {
            if (protocol == "shadowsocksr")
            {
                auto r = ShadowSocksRServerObject::fromJson(outbound);
                return {
                    { INFO_PROTOCOL, "shadowsocksr" }, //
                    { INFO_SERVER, r.address },        //
                    { INFO_PORT, r.port }              //
                };
            }
            return {};
        }
        const QList<QString> SupportedLinkPrefixes() const override
        {
            return { "ssr://" };
        };
        const QList<QString> SupportedProtocols() const override
        {
            return { "shadowsocksr" };
        }
    };
}; // namespace SSRPlugin
