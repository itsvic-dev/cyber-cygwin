#include "language.h"
#include "languageadaptor.h"

Language::Language(QObject *parent)
    : QObject(parent)
    , m_settings(new QSettings(QStringLiteral("cyberos"), QStringLiteral("language")))
{
    new LanguageAdaptor(this);
    QDBusConnection::sessionBus().registerObject(QStringLiteral("/Language"), this);

    if (!m_settings->contains("language"))
        m_settings->setValue("language", "en_US");

    emit languageChanged();
}

QString Language::languageCode() const
{
    return m_settings->value("language").toString();
}

void Language::setLanguage(const QString &code)
{
    m_settings->setValue("language", code);

    emit languageChanged();
}