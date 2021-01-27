#ifndef WINDOWCONTROL_H
#define WINDOWCONTROL_H

#include <QObject>

class WindowControl : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(bool isMaximized READ isMaximized NOTIFY maximizeChanged)

public:
    explicit WindowControl(QObject *parent = nullptr);

    QString title() const;
    bool isMaximized() const;

    Q_INVOKABLE void close();
    Q_INVOKABLE void minimize();
    Q_INVOKABLE void restore();
    Q_INVOKABLE void maximize();
    Q_INVOKABLE void toggleMaximize();

signals:
    void titleChanged();
    void maximizeChanged();

private slots:
    void onWindowChanged();

private:
    QString m_title;
    bool m_isMaximized;
};

#endif // WINDOWCONTROL_H
