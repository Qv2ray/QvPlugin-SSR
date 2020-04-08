#pragma once

#include "common/CommonHelpers.hpp"

#include <QList>
namespace SSRPlugin
{
    QJsonObject GenerateShadowSocksROUT(QList<ShadowSocksRServerObject> servers);
}
