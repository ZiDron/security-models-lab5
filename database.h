#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "file_system_path_right.h"
#include "access_right.h"
#include "role.h"
#include "user.h"
#include <QStringList>

class Database : public QObject{
    Q_OBJECT
public:
    Database();

    enum Changes {
        Add = 0,
        Remove = 1
    };
    bool createNewRight(QString name, int level);
    bool createNewRole(QString name, QList<QString> *rightNames = 0);
    bool createNewUser(QString name, QList<QString> *roleNames = 0);

    QList<AccessRight*> getRightsList();
    QList<Role*> getRoleList();
    QList<User*> getUsersList();
    AccessRight *getAccessRight(QString path);
    void changeRight(QString path, QString rightName);
    void changeRightLevel(QString rightName, int newLevel);
    void changeRole(QString roleName, QList<QString> rightNames, Changes changeType);
    void changeRole(QString roleName, QString rightName, Changes changeType);
    void changeUser(QString userName, QList<QString> roleNames, Changes changeType);
    void changeUser(QString userName, QString roleName, Changes changeType);

    QList<QString> getRightsNameList();
    QList<QString> getRoleNameList();
    QList<QString> getUsersNameList();
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

    QList<FileSystemPathRight*> fileSystemPathRightList;
    QList<AccessRight*> rightsList;
    QList<Role*> roleList;
    QList<User*> usersList;

signals:
    void updated();
};

#endif // DATABASE_H
