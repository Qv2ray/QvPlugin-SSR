#pragma once
#include "3rdparty/shadowsocksr-uvw/src/SSRThread.hpp"
#include "Qv2rayPluginProcessor.hpp"
#include "httpProxy.hpp"
namespace SSRPlugin
{
    class SSRKernelInstance : public Qv2rayPlugin::QvPluginKernel
    {
      public:
        explicit SSRKernelInstance(QObject *parent = nullptr);
        bool StartKernel(const QJsonObject &config) override;
        bool StopKernel() override;
        const QList<Qv2rayPlugin::QvPluginOutboundObject> KernelOutboundCapabilities() const override
        {
            return { { "ShadowSocksR", "shadowsocksr" } };
        }

      private:
        std::unique_ptr<HttpProxy> httpProxy;
        std::unique_ptr<SSRThread> ssrThread;
    };
} // namespace SSRPlugin
