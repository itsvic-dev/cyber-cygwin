#ifndef SORTFILTERPROXYMODEL_H
#define SORTFILTERPROXYMODEL_H

#include <QObject>

class SortFilterProxyModel : public QObject
{
    Q_OBJECT
public:
    explicit SortFilterProxyModel(QObject *parent = nullptr);

signals:

};

#endif // SORTFILTERPROXYMODEL_H
