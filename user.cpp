#include "user.h"


User::User(QString name, QList<Role *> *roles) {
    this->name = name;
    if (roles) {
        this->roles.append(*roles);
    }
}

QString User::getName() {
    return name;
}

QList<Role *> *User::getRole() {
    return &roles;
}
