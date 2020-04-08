#include "SimplePluginKernel.hpp"

SimplePluginKernel::SimplePluginKernel(QObject *parent) : Qv2rayPlugin::QvPluginKernel(parent)
{
}
bool SimplePluginKernel::StartKernel(const QJsonObject)
{
    return true;
}
bool SimplePluginKernel::StopKernel()
{
    emit OnKernelCrashed("Yay!");
    return true;
}
const QMap<QString, QString> SimplePluginKernel::GetKernelOutbounds() const
{
    return { { "Fake outbound", "pseudo" } };
}
