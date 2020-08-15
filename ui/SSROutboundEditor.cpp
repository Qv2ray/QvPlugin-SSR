#include "SSROutboundEditor.hpp"

namespace SSRPlugin
{
    SSROutboundEditor::SSROutboundEditor(QWidget *parent) : Qv2rayPlugin::QvPluginEditor(parent)
    {
        setupUi(this);
    }

    SSROutboundEditor::~SSROutboundEditor()
    {
    }

    QPair<QString, int> SSROutboundEditor::GetHostAddress() const
    {
        return { shadowsocksR.address, shadowsocksR.port };
    }
    void SSROutboundEditor::SetHostAddress(const QString &address, int port)
    {
        shadowsocksR.address = address;
        shadowsocksR.port = port;
    }

    void SSROutboundEditor::SetContent(const QJsonObject &content)
    {
        shadowsocksR.loadJson(content);
        //
        ssrPasswordTxt->setText(shadowsocksR.password);
        ssrMethodCombo->setCurrentText(shadowsocksR.method);
        //
        ssrObfsCombo->setCurrentText(shadowsocksR.obfs);
        ssrObfsParamsTxt->setText(shadowsocksR.obfs_param);
        ssrProtocolCombo->setCurrentText(shadowsocksR.protocol);
        ssrProtocolParamsTxt->setText(shadowsocksR.protocol_param);
    }

    const QJsonObject SSROutboundEditor::GetContent() const
    {
        return shadowsocksR.toJson();
    }

    void SSROutboundEditor::on_ssrPasswordTxt_textEdited(const QString &arg1)
    {
        shadowsocksR.password = arg1;
    }

    void SSROutboundEditor::on_ssrMethodCombo_currentTextChanged(const QString &arg1)
    {
        shadowsocksR.method = arg1;
    }

    void SSROutboundEditor::on_ssrProtocolCombo_currentTextChanged(const QString &arg1)
    {
        shadowsocksR.protocol = arg1;
    }

    void SSROutboundEditor::on_ssrObfsCombo_currentTextChanged(const QString &arg1)
    {
        shadowsocksR.obfs = arg1;
    }

    void SSROutboundEditor::on_ssrProtocolParamsTxt_textEdited(const QString &arg1)
    {
        shadowsocksR.protocol_param = arg1;
    }

    void SSROutboundEditor::on_ssrObfsParamsTxt_textEdited(const QString &arg1)
    {
        shadowsocksR.obfs_param = arg1;
    }

} // namespace SSRPlugin
