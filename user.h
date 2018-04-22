#ifndef USER_H
#define USER_H

#include <QString>
#include <QList>
#include "role.h"

class User {

public:
    User(QString name, QList<Role*> *roles);
    QString getName();
    QList<Role *> *getRole();
    void changeRole(QList<Role*> roleList, int type);

private:
    QString name;
    QList<Role*> roles;
};

#endif // USER_H
