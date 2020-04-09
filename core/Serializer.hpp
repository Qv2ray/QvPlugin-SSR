#pragma once

#include "Qv2rayPluginProcessor.hpp"
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
        const QString SerializeOutbound(const QJsonObject &) const override;
        const QJsonObject DeserializeOutbound(const QString &, QString *alias, QString *errorMessage) const override;
    };
} // namespace SSRPlugin
