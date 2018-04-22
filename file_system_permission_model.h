#ifndef FILE_SYSTEM_PERMISSION_MODEL_H
#define FILE_SYSTEM_PERMISSION_MODEL_H

#include <QFileSystemModel>
#include "database.h"

class FileSystemPermissionModel : public QFileSystemModel {
public:
    FileSystemPermissionModel(Database *database = 0);
    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;


private:
    Database *database;

};

#endif // FILE_SYSTEM_PERMISSION_MODEL_H
