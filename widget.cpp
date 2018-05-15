#include "widget.h"

Widget::Widget(SystemAccessRight *systemAccessRight, Database *database, QWidget *parent) : QWidget(parent),
    userFileSystemView(systemAccessRight, database),
    matrixesWidget(database),
    createItemsWidget(database) {
    userFileSystemView.show();
    matrixesWidget.show();
    createItemsWidget.show();
    hide();
}


Widget::~Widget() {

}

