#pragma once
#include "interface/QvGUIPluginInterface.hpp"
#include "ui/SSROutboundEditor.hpp"
using namespace Qv2rayPlugin;

class SSRGuiInterface : public Qv2rayPlugin::PluginGUIInterface
{

    virtual QIcon Icon() const override
    {
        return QIcon(":/qv2ray.png");
    }
    virtual QList<PluginGuiComponentType> GetComponents() const override
    {
        return { GUI_COMPONENT_OUTBOUND_EDITOR };
    }
    virtual std::unique_ptr<QvPluginSettingsWidget> createSettingsWidgets() const override
    {
        return nullptr;
    }
    virtual QList<typed_plugin_editor> createInboundEditors() const override
    {
        return {};
    }
    virtual QList<typed_plugin_editor> createOutboundEditors() const override
    {
        return { MakeEditorInfoPair<SSROutboundEditor>("shadowsocksr", "ShadowsocksR") };
    }
    virtual std::unique_ptr<QvPluginMainWindowWidget> createMainWindowWidget() const override
    {
        return nullptr;
    }
};
