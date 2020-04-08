
#include "SSRInstance.hpp"

#include "3rdparty/shadowsocksr-uvw/src/SSRThread.hpp"
#include "common/CommonHelpers.hpp"
//#include "KernelInteractions.hpp"
//#include "common/QvHelpers.hpp"
//#include "core/CoreUtils.hpp"
//#include "core/connection/ConnectionIO.hpp"
#include <QJsonArray>
#include <QJsonObject>
#include <memory>

namespace SSRPlugin
{
    ShadowsocksrInstance::ShadowsocksrInstance(QObject *parent) : Qv2rayPlugin::QvPluginKernel(parent)
    {
    }

    bool ShadowsocksrInstance::StartKernel(const QJsonObject &root, const QString &id)
    {
        int socks_local_port = 0;
        int http_local_port = 0;
        QString tag;
        QString listen_address;
        for (const auto &item : root["inbounds"].toArray())
        {
            auto protocol = item.toObject()["protocol"].toString(QObject::tr("N/A"));
            if (protocol == "socks")
            {
                tag = item.toObject()["tag"].toString("");
                socks_local_port = item.toObject()["port"].toInt(0);
                listen_address = item.toObject()["listen"].toString("");
            }
            else if (protocol == "http")
            {
                http_local_port = item.toObject()["port"].toInt(0);
            }
        }
        if (socks_local_port == 0)
        {
            // socks must enabled
            return false;
        }
        auto outbound = root["outbounds"].toArray().first().toObject();
        auto ssrServer = ShadowSocksRServerObject::fromJson(outbound["settings"].toObject()["servers"].toArray().first().toObject());
        auto remotePort = ssrServer.port;
        auto remote_host = ssrServer.address.toStdString();
        auto method = ssrServer.method.toStdString();
        auto password = ssrServer.password.toStdString();
        auto obfs = ssrServer.obfs.toStdString();
        auto obfs_param = ssrServer.obfs_param.toStdString();
        auto protocol = ssrServer.protocol.toStdString();
        auto protocol_param = ssrServer.protocol_param.toStdString();
        ssrThread = std::make_unique<SSRThread>(socks_local_port, remotePort, listen_address.toStdString(), remote_host, method, password, obfs,
                                                obfs_param, protocol, protocol_param, tag);
        ssrThread->connect(ssrThread.get(), &SSRThread::onSSRThreadLog, this, &ShadowsocksrInstance::OnKernelLogAvaliable);
        ssrThread->connect(ssrThread.get(), &SSRThread::OnDataReady, this, &ShadowsocksrInstance::OnKernelStatsAvailable);
        ssrThread->start();
        if (http_local_port != 0)
        {
            httpProxy = std::make_unique<HttpProxy>();
            httpProxy->httpListen(QHostAddress{ listen_address }, http_local_port, socks_local_port);
        }
        return true;
    }

    bool ShadowsocksrInstance::StopKernel()
    {
        if (ssrThread != nullptr && ssrThread->isRunning())
        {
            ssrThread = std::make_unique<SSRThread>();
        }
        httpProxy = nullptr;
        return true;
    }

} // namespace SSRPlugin
