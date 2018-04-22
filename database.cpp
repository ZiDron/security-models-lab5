#include "database.h"

Database::Database() {
    init();

//    QList<QString> roleList = getRoleList();
//    createNewUser("eMotion", &roleList);
    //==== УЖЕ СОЗДАНЫ ======//
//    QList<QString> rightList = getRightsList();
//    createNewRole("Admin", &rightList);
//    createNewRight("NonSecret", 0);
//    createNewRight("Secret", 1);
//    createNewRight("TopSecret", 2);

}

void Database::createNewRight(QString name, int level) {
    rightsList.append(AccessRight(name, level));
    save();
}

void Database::createNewRole(QString name, QList<QString> *rightNames) {
    QList<AccessRight *> rightListTemp;
    if (rightNames) {
        for (int i = 0; i < rightNames->size(); i++) {
            AccessRight* acc = getAccessRightByName(rightNames->at(i));
            if (acc) {
                rightListTemp.append(acc);
            }
        }
    }
    roleList.append(Role(name, &rightListTemp));
    save();
}

void Database::createNewUser(QString name, QList<QString> *roleNames) {
    QList<Role *> roleListTemp;
    if (roleNames) {
        for (int i = 0; i < roleNames->size(); i++) {
            Role *role = getRoleByName(roleNames->at(i));
            if (role) {
                roleListTemp.append(role);
            }
        }
    }
    usersList.append(User(name, &roleListTemp));
    save();
}

AccessRight *Database::getAccessRightByName(QString name) {
    for (int i = 0; i < rightsList.size(); i++) {
        if (rightsList[i].getName() == name) {
            return &rightsList[i];
        }
    }
    return NULL;
}

FileSystemPathRight *Database::getFileSystemPathRighByPath(QString path) {
    for (int i = 0; i < fileSystemPathRightList.size(); i++) {
        if (fileSystemPathRightList[i].getPath() == path) {
            return &fileSystemPathRightList[i];
        }
    }
    return NULL;
}

Role *Database::getRoleByName(QString name) {
    for (int i = 0; i < roleList.size(); i++) {
        if (roleList[i].getName() == name) {
            return &roleList[i];
        }
    }
    return NULL;
}

User *Database::getUserByName(QString name) {
    for (int i = 0; i < usersList.size(); i++) {
        if (usersList[i].getName() == name) {
            return &usersList[i];
        }
    }
    return NULL;
}

QString Database::getLowRightName() {
    for (int i = 0; i < rightsList.size(); i++) {
        if (rightsList[i].getLevel() == 0) {
            return rightsList[i].getName();
        }
    }
}

QList<QString> Database::getRightsList() {
    QList<QString> list;
    for (int i = 0; i < rightsList.size(); i++) {
        list.append(rightsList[i].getName());
    }
    return list;
}

QList<QString> Database::getRoleList() {
    QList<QString> list;
    for (int i = 0; i < roleList.size(); i++) {
        list.append(roleList[i].getName());
    }
    return list;
}

QList<QString> Database::getUsersList() {
    QList<QString> list;
    for (int i = 0; i < usersList.size(); i++) {
        list.append(usersList[i].getName());
    }
    return list;
}

AccessRight *Database::getAccessRight(QString path) {
    FileSystemPathRight *temp = getFileSystemPathRighByPath(path);
    if (temp) {
        return temp->getRights();
    } else {
        return AccessRight::empty(getLowRightName());
    }
}

void Database::changeRight(QString path, QString rightName) {
    FileSystemPathRight *temp = getFileSystemPathRighByPath(path);
    AccessRight *newAccessRight = getAccessRightByName(rightName);
    if (temp) {
        if (newAccessRight) {
            temp->setRight(newAccessRight);
        }
    } else {
        if (newAccessRight) {
            fileSystemPathRightList.append(FileSystemPathRight(path, newAccessRight));
        }
    }
    save();
}

void Database::changeRole(QString roleName, QList<QString> rightNames, Database::Changes changeType) {
    Role *role = getRoleByName(roleName);
    QList<AccessRight*> tempAccesRight;
    if (role) {
        for (int i = 0; i < rightNames.size(); i++) {
            AccessRight *acc;
            acc = getAccessRightByName(rightNames.at(i));
            if (acc) {
                tempAccesRight.append(acc);
            }
        }
        role->changePermissions(tempAccesRight, changeType);
    }
    save();
}

void Database::changeUser(QString userName, QList<QString> roleNames, Database::Changes changeType) {
    User *user = getUserByName(userName);
    QList<Role*> tempRoleList;
    if (user) {
        for (int i = 0; i < roleNames.size(); i++) {
            Role* tempRole = getRoleByName(roleNames.at(i));
            if (tempRole) {
                tempRoleList.append(tempRole);
            }
        }
        user->changeRole(tempRoleList, changeType);
    }
    save();
}

void Database::init() {
    QString filesRightsPath = "data/filesRights.txt";
    QString rightListPath = "data/rightList.txt";
    QString roleListPath = "data/roleList.txt";
    QString userListPath = "data/userList.txt";

    filesSystemPathFile.setFileName(filesRightsPath);
    rightListFile.setFileName(rightListPath);
    roleListFile.setFileName(roleListPath);
    userListFile.setFileName(userListPath);

    if (!filesSystemPathFile.open(QIODevice::ReadWrite)) {
        qDebug() << "Cant open %s" << filesSystemPathFile.fileName();
    }
    if (!rightListFile.open(QIODevice::ReadWrite)) {
        qDebug() << "Cant open %s" << rightListFile.fileName();
    }
    if (!roleListFile.open(QIODevice::ReadWrite)) {
        qDebug() << "Cant open %s" << roleListFile.fileName();
    }
    if (!userListFile.open(QIODevice::ReadWrite)) {
        qDebug() << "Cant open " << userListFile.fileName();
    }

    while (!rightListFile.atEnd()) {
        QString line = rightListFile.readLine();
        QStringList list = line.split(" ", QString::SkipEmptyParts);
        if (list.size() == 2) {
            rightsList.append(AccessRight(list[0], list[1].toInt()));
        }
    }

    while (!roleListFile.atEnd()) {
        QString line = roleListFile.readLine();
        QStringList list = line.split(" ", QString::SkipEmptyParts);

        QList<AccessRight*> initAccessRightList;
        for (int i = 1; i < list.size(); i++) {
            AccessRight *right = getAccessRightByName(list[i]);
            if (right) {
                initAccessRightList.append(right);
            }
        }

        if (list.size()) {
            roleList.append(Role(list[0], &initAccessRightList));
        }
    }

    while (!userListFile.atEnd()) {
        QString line = userListFile.readLine();
        QStringList list = line.split(" ", QString::SkipEmptyParts);

        QList<Role*> initRoleList;
        for (int i = 1; i < list.size(); i++) {
            Role *role = getRoleByName(list[i]);
            if (role) {
                initRoleList.append(role);
            }
        }

        if (list.size()) {
            usersList.append(User(list[0], &initRoleList));
        }
    }

    while (!filesSystemPathFile.atEnd()) {
        QString line = filesSystemPathFile.readLine();
        QStringList list = line.split(" ", QString::SkipEmptyParts);
        if (list.size() == 2) {
            AccessRight *acc = getAccessRightByName(list[1]);
            if (acc) {
                fileSystemPathRightList.append(FileSystemPathRight(list[0], acc));
            }
        }
    }
}

void Database::save() {
    rightListFile.seek(0);
    rightListFile.resize(0);
    roleListFile.seek(0);
    roleListFile.resize(0);

    QTextStream out(&rightListFile);
    for (int i = 0; i < rightsList.size(); i++) {
        out << rightsList[i].getName() << " " << rightsList[i].getLevel() << "\n";
    }

    out.setDevice(&roleListFile);
    for (int i = 0; i < roleList.size(); i++) {
        out << roleList[i].getName() << " ";
        for (int j = 0; j < roleList[i].getPermisions()->size(); j++) {
            out << roleList[i].getPermisions()->at(j)->getName() << " ";
        }
        out << "\n";
    }
    out.setDevice(&userListFile);
    for (int i = 0; i < usersList.size(); i++) {
        out << usersList[i].getName() << " ";
        for (int j = 0; j < usersList[i].getRole()->size(); j++) {
            out << usersList[i].getRole()->at(j)->getName() << " ";
        }
        out << "\n";
    }

    out.setDevice(&filesSystemPathFile);
    for (int i = 0; i < fileSystemPathRightList.size(); i++) {
        out << fileSystemPathRightList[i].getPath() << " " << fileSystemPathRightList[i].getRights()->getName() << " ";
    }
}
