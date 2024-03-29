#pragma once

#include "QvPluginProcessor.hpp"
#include "common/CommonHelpers.hpp"

#include <QList>
using namespace Qv2rayPlugin;
class SSRSerializer : public Qv2rayPlugin::PluginOutboundHandler
{
  public:
    explicit SSRSerializer() : PluginOutboundHandler(){};
    const QString SerializeOutbound(const QString &protocol,  //
                                    const QString &alias,     //
                                    const QString &groupName, //
                                    const QJsonObject &object, const QJsonObject &) const override;
    const QPair<QString, QJsonObject> DeserializeOutbound(const QString &link, QString *alias, QString *errorMessage) const override;
    const void SetOutboundInfo(const QString &protocol, const OutboundInfoObject &info, QJsonObject &outbound) const override
    {
        if (protocol != "shadowsocksr")
            return;
        if (info.contains(INFO_SERVER))
            outbound["address"] = info[INFO_SERVER].toString();
        if (info.contains(INFO_PORT))
            outbound["port"] = info[INFO_PORT].toInt();
    }
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
