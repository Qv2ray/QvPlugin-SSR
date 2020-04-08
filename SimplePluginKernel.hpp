#pragma once
#include "Qv2rayPluginObjects.hpp"

class SimplePluginKernel : public Qv2rayPlugin::QvPluginKernel
{
  public:
    explicit SimplePluginKernel(QObject *parent = nullptr);
    bool StartKernel(const QJsonObject config) override;
    bool StopKernel() override;
    const QMap<QString, QString> GetKernelOutbounds() const override;
};
