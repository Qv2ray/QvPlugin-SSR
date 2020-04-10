#pragma once

#include "Qv2rayPluginProcessor.hpp"
#include "common/CommonHelpers.hpp"
#include "ui_SSROutboundEditor.h"

#include <QWidget>

namespace SSRPlugin
{
    class SSROutboundEditor
        : public Qv2rayPlugin::QvPluginEditor
        , private Ui::SSROutboundEditor
    {
        Q_OBJECT

      public:
        explicit SSROutboundEditor(QWidget *parent = nullptr);
        ~SSROutboundEditor();
        void SetHostInfo(const QString &address, int port) override;
        void SetContent(const QJsonObject &) override;
        QPair<QString, int> GetHostInfo() const override;
        const QJsonObject GetContent() const override;
        //
        void SwitchOutbound(const QString &) override{};
        QList<Qv2rayPlugin::QvPluginOutboundObject> OutboundCapabilities() const override
        {
            return { { "shadowsocksr", "ShadowSocksR" } };
        }
      private slots:
        void on_ssrPasswordTxt_textEdited(const QString &arg1);
        void on_ssrMethodCombo_currentTextChanged(const QString &arg1);
        void on_ssrProtocolCombo_currentTextChanged(const QString &arg1);
        void on_ssrObfsCombo_currentTextChanged(const QString &arg1);
        void on_ssrProtocolParamsTxt_textEdited(const QString &arg1);
        void on_ssrObfsParamsTxt_textEdited(const QString &arg1);

      private:
        ShadowSocksRServerObject shadowsocksR;
    };

} // namespace SSRPlugin
