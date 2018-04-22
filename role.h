#ifndef ROLE_H
#define ROLE_H

#include <QList>
#include "access_right.h"

class Role {

public:
    Role(QString name, QList<AccessRight *> *permisions = 0);
    QString getName();
    QList<AccessRight*> *getPermisions();
    void changePermissions(QList<AccessRight*> accesRight, int type);

private:
    QString name;
    QList<AccessRight*> permisions;
};

#endif // ROLE_H
