#include "access_right.h"

AccessRight AccessRight::emptyRight("", 0);

AccessRight::AccessRight(QString name, int level) {
    this->name = name;
    this->level = level;
}

QString AccessRight::getName() const {
    return name;
}

int AccessRight::getLevel() {
    return level;
}

void AccessRight::setLevel(int level) {
    this->level = level;
}

AccessRight *AccessRight::empty(QString name) {
    emptyRight.name = name;
    return &emptyRight;
}
