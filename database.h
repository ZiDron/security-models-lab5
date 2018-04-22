#ifndef DATABASE_H
#define DATABASE_H

#include <QList>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "file_system_path_right.h"
#include "access_right.h"
#include "role.h"
#include "user.h"

class Database {

public:
    Database();
    void createNewRight(QString name, int level);
    void createNewRole(QString name, QList<QString> *rightNames = 0);
    void createNewUser(QString name, QList<QString> *roleNames = 0);

    QList<QString> getRightsList();
    QList<QString> getRoleList();
    QList<QString> getUsersList();
    AccessRight *getAccessRight(QString path);
    void changeRight(QString path, QString rightName);

private:
    AccessRight *getAccessRightByName(QString name);
    FileSystemPathRight *getFileSystemPathRighByPath(QString path);
    Role *getRoleByName(QString name);
    User *getUserByName(QString name);

    QString getLowRightName();

    void init();
    void save();

    QFile filesSystemPathFile;
    QFile rightListFile;
    QFile roleListFile;
    QFile userListFile;

    QList<FileSystemPathRight> fileSystemPathRightList;
    QList<AccessRight> rightsList;
    QList<Role> roleList;
    QList<User> usersList;
};

#endif // DATABASE_H
