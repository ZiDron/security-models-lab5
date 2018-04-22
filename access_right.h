#ifndef ACCESSRIGHT_H
#define ACCESSRIGHT_H

#include <QString>

class AccessRight {

public:
    AccessRight(QString name, int level);
    QString getName() const;
    int getLevel();
    void changeLevel(int level);
    static AccessRight *empty(QString name);

private:
    static AccessRight emptyRight;
    QString name;
    int level;
};

#endif // ACCESSRIGHT_H
