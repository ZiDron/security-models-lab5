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

private:
    Database database;
    SystemAccessRight systemAccessRight;
    Widget widget;
};

#endif // APPLICATION_H
