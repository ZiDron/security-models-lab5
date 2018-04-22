#ifndef SYSTEMACCESSRIGHT_H
#define SYSTEMACCESSRIGHT_H

#include <QList>
#include <QObject>
#include <QPair>
#include <QDir>
#include <QFileInfo>
#include "database.h"


class SystemAccessRight : public QObject {
    Q_OBJECT
public:

    SystemAccessRight(Database *database);
//    void changeRight(QString path, AccessRight right);
//    void changeRight(QString path, QString rightName);
//    AccessRight getAccessRight(QString path);
    bool copy(QString srcPath, QString dstPath);

private:
    Database *database;
    bool trueCopy(QString srcPath, QString dstPath);
//    bool pathExist(QString path);
//    int findIndexPath(QString path);
//    QList<QPair<QString, AccessRight> > rightList;

signals:
    void wrongAccessRights(QString srcFolderPath, QString dstFolderPath);

};

#endif // SYSTEMACCESSRIGHT_H
