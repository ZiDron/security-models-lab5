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
        } else {
            return QVariant();
        }

    } else {
        return QFileSystemModel::data(index, role);
    }

    if (index.column() == 4 && role == Qt::FontRole) {
        QModelIndex fontIndex = this->index(index.row(), index.column() - 1, index.parent());
        return QFileSystemModel::data(fontIndex);
    }
}

int FileSystemPermissionModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 5;
}
