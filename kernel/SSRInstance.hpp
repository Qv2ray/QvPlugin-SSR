#pragma once
#include "3rdparty/shadowsocksr-uvw/src/SSRThread.hpp"
#include "Qv2rayPluginObjects.hpp"
#include "httpProxy.hpp"
namespace SSRPlugin
{
    class ShadowsocksrInstance : public Qv2rayPlugin::QvPluginKernel
    {
      public:
        explicit ShadowsocksrInstance(QObject *parent = nullptr);
        bool StartKernel(const QJsonObject &config, const QString &id) override;
        bool StopKernel() override;
        const QMap<QString, QString> GetKernelOutbounds() const override
        {
            return { { "ShadowSocksR", "shadowsocksr" } };
        }

      private:
        std::unique_ptr<HttpProxy> httpProxy;
        std::unique_ptr<SSRThread> ssrThread;
    };
} // namespace SSRPlugin
