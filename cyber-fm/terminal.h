#ifndef TERMINAL_H
#define TERMINAL_H

#include <QObject>

class Terminal : public QObject
{
    Q_OBJECT
public:
    explicit Terminal(QObject *parent = nullptr);

signals:

};

#endif // TERMINAL_H
