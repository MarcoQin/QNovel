#ifndef GLOBALMANAGER_H
#define GLOBALMANAGER_H

#include <QObject>

class GlobalManager : public QObject
{
    Q_OBJECT
public:
    explicit GlobalManager(QObject *parent = 0);

signals:

public slots:
};

#endif // GLOBALMANAGER_H