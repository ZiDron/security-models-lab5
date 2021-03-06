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

bool Database::createNewRight(QString name, int level) {
    if (getAccessRightByName(name)) {
        return false;
    }
    rightsList.append(new AccessRight(name, level));
    save();
    emit updated();
    return true;
}

bool Database::createNewRole(QString name, QList<QString> *rightNames) {
    if (getRoleByName(name)) {
        return false;
    }

    QList<AccessRight *> rightListTemp;
    if (rightNames) {
        for (int i = 0; i < rightNames->size(); i++) {
            AccessRight* acc = getAccessRightByName(rightNames->at(i));
            if (acc) {
                rightListTemp.append(acc);
            }
        }
    }
    roleList.append(new Role(name, rightListTemp));
    save();
    emit updated();
    return true;
}

bool Database::createNewUser(QString name, QList<QString> *roleNames) {
    if (getUserByName(name)) {
        return false;
    }

    QList<Role *> roleListTemp;
    if (roleNames) {
        for (int i = 0; i < roleNames->size(); i++) {
            Role *role = getRoleByName(roleNames->at(i));
            if (role) {
                roleListTemp.append(role);
            }
        }
    }
    usersList.append(new User(name, roleListTemp));
    save();
    emit updated();
    return true;
}

bool Database::removeRight(QString name) {
    AccessRight *right = getAccessRightByName(name);

    if (!right) {
        return false;
    }

    rightsList.removeAll(right); /// удаление самого правила

    for (int i = 0; i < fileSystemPathRightList.size(); i++) {
        if (fileSystemPathRightList.at(i)->getRights() == right) {
            fileSystemPathRightList.at(i)->setRight(getAccessRightByName(getLowRightName()));  /// устанавливаем новое наимешьнее правило для пути
        }
    }

    for (int i = 0; i < roleList.size(); i++) {
        if (roleList.at(i)->getPermisions()->contains(right)) {
            roleList.at(i)->getPermisions()->removeAll(right);
        }
    }
    emit updated();
    return true;
}

bool Database::removeRole(QString name) {
    Role *role = getRoleByName(name);

    if (!role) {
        return false;
    }

    roleList.removeAll(role);

    for (int i = 0; i < usersList.size(); i++) {
        if (usersList.at(i)->getRole()->contains(role)) {
            usersList.at(i)->getRole()->removeAll(role);
        }
    }
    emit updated();
    return true;
}

bool Database::removeUser(QString name) {
    User *user = getUserByName(name);

    if (!user) {
        return false;
    }

    usersList.removeAll(user);
    emit updated();
    return true;
}

QList<AccessRight *> Database::getRightsList() {
    return rightsList;
}

QList<Role *> Database::getRoleList() {
    return roleList;
}

QList<User *> Database::getUsersList() {
    return usersList;
}

AccessRight *Database::getHighestRight() {
    AccessRight *r = rightsList.at(0);
    for (int i = 0; i < rightsList.size(); i++) {
        if (rightsList[i]->getLevel() > r->getLevel()) {
            r = rightsList[i];
        }
    }
    return r;
}

AccessRight *Database::getAccessRightByName(QString name) {
    for (int i = 0; i < rightsList.size(); i++) {
        if (rightsList[i]->getName() == name) {
            return rightsList[i];
        }
    }
    return NULL;
}

FileSystemPathRight *Database::getFileSystemPathRighByPath(QString path) {
    for (int i = 0; i < fileSystemPathRightList.size(); i++) {
        if (fileSystemPathRightList[i]->getPath() == path) {
            return fileSystemPathRightList[i];
        }
    }
    return NULL;
}

Role *Database::getRoleByName(QString name) {
    for (int i = 0; i < roleList.size(); i++) {
        if (roleList[i]->getName() == name) {
            return roleList[i];
        }
    }
    return NULL;
}

User *Database::getUserByName(QString name) {
    for (int i = 0; i < usersList.size(); i++) {
        if (usersList[i]->getName() == name) {
            return usersList[i];
        }
    }
    return NULL;
}

QString Database::getLowRightName() {
    for (int i = 0; i < rightsList.size(); i++) {
        if (rightsList[i]->getLevel() == 0) {
            return rightsList[i]->getName();
        }
    }
}

QList<QString> Database::getRightsNameList() {
    QList<QString> list;
    for (int i = 0; i < rightsList.size(); i++) {
        list.append(rightsList[i]->getName());
    }
    return list;
}

QList<QString> Database::getRoleNameList() {
    QList<QString> list;
    for (int i = 0; i < roleList.size(); i++) {
        list.append(roleList[i]->getName());
    }
    return list;
}

QList<QString> Database::getUsersNameList() {
    QList<QString> list;
    for (int i = 0; i < usersList.size(); i++) {
        list.append(usersList[i]->getName());
    }
    return list;
}

AccessRight *Database::getAccessRight(QString path) {
    FileSystemPathRight *temp = getFileSystemPathRighByPath(path);
    if (temp) {
        return temp->getRights();
    } else {
        return getAccessRightByName(getLowRightName());
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
            fileSystemPathRightList.append(new FileSystemPathRight(path, newAccessRight));
        }
    }
    save();
    emit updated();
}

void Database::changeRightLevel(QString rightName, int newLevel) {
    AccessRight *acc = getAccessRightByName(rightName);
    if (acc) {
        acc->changeLevel(newLevel);
    }
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
    emit updated();
}

void Database::changeRole(QString roleName, QString rightName, Database::Changes changeType) {
    QList<QString> l;
    l.append(rightName);
    changeRole(roleName, l, changeType);
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
    emit updated();
}

void Database::changeUser(QString userName, QString roleName, Database::Changes changeType) {
    QList<QString> l;
    l.append(roleName);
    changeUser(userName, l, changeType);
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
        line.remove('\n');
        QStringList list = line.split(" ", QString::SkipEmptyParts);
        if (list.size() == 2) {
            rightsList.append(new AccessRight(list[0], list[1].toInt()));
        }
    }

    while (!roleListFile.atEnd()) {
        QString line = roleListFile.readLine();
        line.remove('\n');
        QStringList list = line.split(" ", QString::SkipEmptyParts);

        QList<AccessRight*> initAccessRightList;
        for (int i = 1; i < list.size(); i++) {
            AccessRight *right = getAccessRightByName(list[i]);
            if (right) {
                initAccessRightList.append(right);
            }
        }

        if (list.size()) {
            roleList.append(new Role(list[0], initAccessRightList));
        }
    }

    while (!userListFile.atEnd()) {
        QString line = userListFile.readLine();
        line.remove('\n');
        QStringList list = line.split(" ", QString::SkipEmptyParts);

        QList<Role*> initRoleList;
        for (int i = 1; i < list.size(); i++) {
            Role *role = getRoleByName(list[i]);
            if (role) {
                initRoleList.append(role);
            }
        }

        if (initRoleList.size()) {
            usersList.append(new User(list[0], initRoleList));
        }
    }

    while (!filesSystemPathFile.atEnd()) {
        QString line = filesSystemPathFile.readLine();
        QStringList list = line.split(" ", QString::SkipEmptyParts);
        if (list.size() == 2) {
            AccessRight *acc = getAccessRightByName(list[1]);
            if (acc) {
                fileSystemPathRightList.append(new FileSystemPathRight(list[0], acc));
            }
        }
    }
    filesSystemPathFile.close();
    rightListFile.close();
    roleListFile.close();
    userListFile.close();
}

void Database::save() {
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
    filesSystemPathFile.seek(0);
    filesSystemPathFile.resize(0);
    rightListFile.seek(0);
    rightListFile.resize(0);
    roleListFile.seek(0);
    roleListFile.resize(0);
    userListFile.seek(0);
    userListFile.resize(0);

    QTextStream out(&rightListFile);
    for (int i = 0; i < rightsList.size(); i++) {
        out << rightsList[i]->getName() << " " << rightsList[i]->getLevel() << "\n";
    }

    out.setDevice(&roleListFile);
    for (int i = 0; i < roleList.size(); i++) {
        out << roleList[i]->getName() << " ";
        for (int j = 0; j < roleList[i]->getPermisions()->size(); j++) {
            out << roleList[i]->getPermisions()->at(j)->getName() << " ";
        }
        out << "\n";
    }
    out.setDevice(&userListFile);
    for (int i = 0; i < usersList.size(); i++) {
        out << usersList[i]->getName() << " ";
        for (int j = 0; j < usersList[i]->getRole()->size(); j++) {
            out << usersList[i]->getRole()->at(j)->getName() << " ";
        }
        out << "\n";
    }

    out.setDevice(&filesSystemPathFile);
    for (int i = 0; i < fileSystemPathRightList.size(); i++) {
        out << fileSystemPathRightList[i]->getPath() << " " << fileSystemPathRightList[i]->getRights()->getName() << " ";
    }
    filesSystemPathFile.close();
    rightListFile.close();
    roleListFile.close();
    userListFile.close();
}
