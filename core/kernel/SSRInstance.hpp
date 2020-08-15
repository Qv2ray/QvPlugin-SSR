#pragma once
#include "3rdparty/shadowsocksr-uvw/src/SSRThread.hpp"
#include "QvPluginProcessor.hpp"
#include "common/CommonHelpers.hpp"
#include "utils/HttpProxy.hpp"

using namespace Qv2rayPlugin;

namespace SSRPlugin
{
    class SSRKernelInstance : public Qv2rayPlugin::PluginKernel
    {
      public:
        explicit SSRKernelInstance();
        bool StartKernel() override;
        bool StopKernel() override;
        void SetConnectionSettings(const QMap<KernelOptionFlags, QVariant> &options, const QJsonObject &settings) override;

      private:
        int socks_local_port;
        int http_local_port;
        bool enable_udp;
        QString listen_address;
        ShadowSocksRServerObject outbound;
        std::unique_ptr<Qv2rayPlugin::Utils::HttpProxy> httpProxy;
        std::unique_ptr<SSRThread> ssrThread;
    };

    class SSRKernelInterface : public Qv2rayPlugin::PluginKernelInterface
    {
      public:
        std::unique_ptr<PluginKernel> CreateKernel() const override
        {
            return std::make_unique<SSRKernelInstance>();
        }
        QList<QString> GetKernelProtocols() const override
        {
            return { "shadowsocksr" };
        }
    };
} // namespace SSRPlugin
