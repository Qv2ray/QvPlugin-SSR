#include "CommonHelpers.hpp"

#include <QByteArray>

namespace SSRPlugin
{
    QString SafeBase64Decode(QString string)
    {
        QByteArray ba = string.replace(QChar('-'), QChar('+')).replace(QChar('_'), QChar('/')).toUtf8();
        return QByteArray::fromBase64(ba, QByteArray::Base64Option::OmitTrailingEquals);
    }

    QString SafeBase64Encode(const QString &string, bool trim)
    {
        QString base64 = string.toUtf8().toBase64();
        if (trim)
        {
            auto tmp = base64.replace(QChar('+'), QChar('-')).replace(QChar('/'), QChar('_'));
            auto crbedin = tmp.crbegin();
            auto idx = tmp.length();
            while (crbedin != tmp.crend() && (*crbedin) == '=') idx -= 1, crbedin++;
            return idx != tmp.length() ? tmp.remove(idx, tmp.length() - idx) : tmp;
        }
        else
        {
            return base64.replace(QChar('+'), QChar('-')).replace(QChar('/'), QChar('_'));
        }
    }

} // namespace SSRPlugin
