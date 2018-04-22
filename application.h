#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QDebug>
#include "widget.h"
#include "system_access_right.h"
#include "database.h"

class Application : public QObject {
    Q_OBJECT
public:
    Application();
    void show();
//    void changeAccessRight(QDir *folder, SystemAccessRight::AccessRight right);
//    void changeAccessRight(QString path, SystemAccessRight::AccessRight right);
//    SystemAccessRight::AccessRight getAccessRight(QString path);

private:
    Database database;
    SystemAccessRight systemAccessRight;
    Widget widget;
};

#endif // APPLICATION_H
