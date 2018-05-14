#include "user.h"


User::User(QString name, QList<Role *> roles) {
    this->name = name;
    if (!roles.isEmpty()) {
        this->roles.append(roles);
    }
}

QString User::getName() const {
    return name;
}

QList<Role *> *User::getRole() {
    return &roles;
}

QList<AccessRight *> User::getRights() const {
    QList<AccessRight*> list;
    for (int i = 0; i < roles.count(); i++) {
        list.append(*(roles.at(i)->getPermisions()));
    }
    return list;
}

void User::changeRole(QList<Role *> roleList, int type) {
    if (type) {
        for (int i = 0; i < roleList.size(); i++) {
            if (roles.contains(roleList.at(i))) {
                roles.removeOne(roleList.at(i));
            }
        }
    } else {
        for (int i = 0; i < roleList.size(); i++) {
            if (!roles.contains(roleList.at(i))) {
                roles.append(roleList.at(i));
            }
        }
    }
}
