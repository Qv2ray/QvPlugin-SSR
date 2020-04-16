
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

    void SSRKernelInstance::SetConnectionSettings(const QString &listenAddress, const QMap<QString, int> &inbound, const QJsonObject &settings)
    {
        this->listen_address = listenAddress;
        socks_local_port = inbound["socks"];
        http_local_port = inbound["http"];
        outbound.loadJson(settings);
    }

    bool SSRKernelInstance::StartKernel()
    {
        auto remotePort = outbound.port;
        auto remote_host = outbound.address.toStdString();
        auto method = outbound.method.toStdString();
        auto password = outbound.password.toStdString();
        auto obfs = outbound.obfs.toStdString();
        auto obfs_param = outbound.obfs_param.toStdString();
        auto protocol = outbound.protocol.toStdString();
        auto protocol_param = outbound.protocol_param.toStdString();
        ssrThread = std::make_unique<SSRThread>(socks_local_port,             //
                                                remotePort,                   //
                                                listen_address.toStdString(), //
                                                remote_host,                  //
                                                method,                       //
                                                password,                     //
                                                obfs,                         //
                                                obfs_param,                   //
                                                protocol,                     //
                                                protocol_param);
        ssrThread->connect(ssrThread.get(), &SSRThread::onSSRThreadLog, this, &SSRKernelInstance::OnKernelLogAvaliable);
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
