#include "file_system_permission_model.h"

FileSystemPermissionModel::FileSystemPermissionModel(Database *database) : QFileSystemModel() {
    this->database = database;
}

QVariant FileSystemPermissionModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (section == 4) {
        return QString("Permission");
    } else {
        return QFileSystemModel::headerData(section, orientation, role);
    }
}

QVariant FileSystemPermissionModel::data(const QModelIndex &index, int role) const {
    if (index.column() == 4 && role == Qt::DisplayRole && database) {
        if (isDir(index)) {
            return  database->getAccessRight(filePath(index))->getName();
//            if (r == SystemAccessRight::NonSecret) {
//                return QString("Non Secret");
//            } else if (r == SystemAccessRight::Secret) {
//                return QString("Secret");
//            } else if (r == SystemAccessRight::TopSecret) {
//                return QString("Top Secret");
//            } else {
//                return QString("");
//            }
        } else {
            return QVariant();
        }

    } else {
        return QFileSystemModel::data(index, role);
    }
}

int FileSystemPermissionModel::columnCount(const QModelIndex &parent) const {
    return 5;
}
