#pragma once
#include "3rdparty/shadowsocksr-uvw/src/SSRThread.hpp"
#include "QvPluginProcessor.hpp"
#include "common/CommonHelpers.hpp"
#include "httpProxy.hpp"
namespace SSRPlugin
{
    class SSRKernelInstance : public Qv2rayPlugin::QvPluginKernel
    {
      public:
        explicit SSRKernelInstance(QObject *parent = nullptr);
        bool StartKernel() override;
        bool StopKernel() override;
        void SetConnectionSettings(const QString &listen_address, const QMap<QString, int> &inbound, const QJsonObject &settings) override;
        const QList<Qv2rayPlugin::QvPluginOutboundObject> KernelOutboundCapabilities() const override
        {
            return { { "ShadowSocksR", "shadowsocksr" } };
        }

      private:
        int socks_local_port;
        int http_local_port;
        QString listen_address;
        ShadowSocksRServerObject outbound;
        std::unique_ptr<HttpProxy> httpProxy;
        std::unique_ptr<SSRThread> ssrThread;
    };
} // namespace SSRPlugin
