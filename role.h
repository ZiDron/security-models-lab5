#ifndef ROLE_H
#define ROLE_H

#include <QList>
#include "access_right.h"

class Role {

public:
    Role(QString name, QList<AccessRight *> *permisions = 0);
    QString getName();
    QList<AccessRight*> *getPermisions();

private:
    QString name;
    QList<AccessRight*> permisions;
};

#endif // ROLE_H
