#include "role.h"

Role::Role(QString name, QList<AccessRight*> *permisions) {
    this->name = name;
    if (permisions) {
        this->permisions.append(*permisions);
    }
}

QString Role::getName() {
    return name;
}

QList<AccessRight *> *Role::getPermisions() {
    return &permisions;
}
