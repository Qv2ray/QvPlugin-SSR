
#include "SSRInstance.hpp"

#include "3rdparty/shadowsocksr-uvw/src/SSRThread.hpp"
#include "common/CommonHelpers.hpp"

#include <QJsonArray>
#include <QJsonObject>
#include <memory>

namespace SSRPlugin
{
    SSRKernelInstance::SSRKernelInstance(QObject *parent) : Qv2rayPlugin::QvPluginKernel(parent)
    {
    }

    void SSRKernelInstance::SetConnectionSettings(const QMap<KernelSetting, QVariant> &options, const QJsonObject &settings)
    {
        this->listen_address = options[KERNEL_LISTEN_ADDRESS].toString();
        socks_local_port = options[KERNEL_SOCKS_ENABLED].toBool() ? options[KERNEL_SOCKS_PORT].toInt() : 0;
        http_local_port = options[KERNEL_HTTP_ENABLED].toBool() ? options[KERNEL_HTTP_PORT].toInt() : 0;
        enable_udp = options[KERNEL_SOCKS_UDP_ENABLED].toBool();
        outbound.loadJson(settings);
    }

    bool SSRKernelInstance::StartKernel()
    {
        if (socks_local_port == 0 && http_local_port == 0)
        {
            emit OnKernelCrashed("Both HTTP and SOCKS are not enabled");
            return false;
        }
        // If the socks has been disabled
        if (socks_local_port == 0)
            socks_local_port = http_local_port + 1;
        auto remotePort = outbound.port;
        auto remote_host = outbound.address.toStdString();
        auto method = outbound.method.toStdString();
        auto password = outbound.password.toStdString();
        auto obfs = outbound.obfs.toStdString();
        auto obfs_param = outbound.obfs_param.toStdString();
        auto protocol = outbound.protocol.toStdString();
        auto protocol_param = outbound.protocol_param.toStdString();
        auto mode = static_cast<SSRThread::SSR_WORK_MODE>(enable_udp);
        ssrThread = std::make_unique<SSRThread>(socks_local_port,             //
                                                remotePort,                   //
                                                60000, 1500, mode,            //
                                                listen_address.toStdString(), //
                                                remote_host,                  //
                                                method,                       //
                                                password,                     //
                                                obfs,                         //
                                                obfs_param,                   //
                                                protocol,                     //
                                                protocol_param);
        ssrThread->connect(ssrThread.get(), &SSRThread::onSSRThreadLog, this, &SSRKernelInstance::OnKernelLogAvailable);
        ssrThread->connect(ssrThread.get(), &SSRThread::OnDataReady, this, &SSRKernelInstance::OnKernelStatsAvailable);
        ssrThread->start();
        if (http_local_port != 0)
        {
            httpProxy = std::make_unique<Qv2rayPlugin::Utils::HttpProxy>();
            httpProxy->httpListen(QHostAddress{ listen_address }, http_local_port, socks_local_port);
        }
        return true;
    }

    bool SSRKernelInstance::StopKernel()
    {
        ssrThread.reset();
        httpProxy.reset();
        ssrThread = nullptr;
        httpProxy = nullptr;
        return true;
    }

} // namespace SSRPlugin
