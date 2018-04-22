#ifndef FILESYSTEMPATHRIGHT_H
#define FILESYSTEMPATHRIGHT_H

#include "access_right.h"

class FileSystemPathRight {

public:
    FileSystemPathRight(QString path, AccessRight *right);
    QString getPath();
    AccessRight *getRights();
    void setRight(AccessRight *newAccesRight);

private:
    QString path;
    AccessRight *right;
};

#endif // FILESYSTEMPATHRIGHT_H
