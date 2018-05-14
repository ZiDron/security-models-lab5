#include "permission_filter_model.h"

PermissionFilterModel::PermissionFilterModel(Database *database) : QSortFilterProxyModel() {
    this->database = database;
    user = 0;
}

void PermissionFilterModel::setUser(User *value) {
    user = value;
}

bool PermissionFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    if (!user) {
        return true;
    }

    QFileSystemModel *model = dynamic_cast<QFileSystemModel*>(this->sourceModel());
    if (model) {
        QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
        QString path = model->filePath(index);
        QList<AccessRight*> rights = user->getRights();
        AccessRight* r = database->getAccessRight(path);
        if (rights.contains(r)) {
            return true;
        } else {
            return false;
        }
    }
}
