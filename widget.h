#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "file_system_view_widget.h"
#include "matrixes_widget.h"
#include "create_items_widget.h"

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(SystemAccessRight *systemAccessRight,
           Database *database,
           QWidget *parent = 0);
    ~Widget();

private:
    FileSystemViewWidget userFileSystemView;
    MatrixesWidget matrixesWidget;
    CreateItemsWidget createItemsWidget;
};

#endif // WIDGET_H
