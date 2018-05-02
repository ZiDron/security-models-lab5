#include "role.h"

Role::Role(QString name, QList<AccessRight*> permisions) {
    this->name = name;
    if (!permisions.isEmpty()) {
        this->permisions.append(permisions);
    }
}

QString Role::getName() const {
    return name;
}

QList<AccessRight *> *Role::getPermisions() {
    return &permisions;
}

void Role::changePermissions(QList<AccessRight *> accesRight, int type) {
    if (type) {
        for (int i = 0; i < accesRight.size(); i++) {
            if (permisions.contains(accesRight.at(i))) {
                permisions.removeOne(accesRight.at(i));
            }
        }
    } else {
        for (int i = 0; i < accesRight.size(); i++) {
            if (!permisions.contains(accesRight.at(i))) {
                permisions.append(accesRight.at(i));
            }
        }
    }
}
