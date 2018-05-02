#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "file_system_view_widget.h"
#include "role_matrix_widget.h"

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(SystemAccessRight *systemAccessRight,
           Database *database,
           QWidget *parent = 0);
    ~Widget();

private:
    FileSystemViewWidget userFileSystemView;
    RoleMatrixWidget roleMatrix;



};

#endif // WIDGET_H
