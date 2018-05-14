#ifndef PERMISSION_FILTER_MODEL_H
#define PERMISSION_FILTER_MODEL_H

#include <QSortFilterProxyModel>
#include <QFileSystemModel>
#include "database.h"
#include "user.h"

class PermissionFilterModel : public QSortFilterProxyModel {
public:
    PermissionFilterModel(Database *database);
    void setUser(User *value);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:
    Database *database;
    User *user;
};

#endif // PERMISSION_FILTER_MODEL_H
