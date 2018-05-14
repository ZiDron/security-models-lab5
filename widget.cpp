#include "widget.h"

Widget::Widget(SystemAccessRight *systemAccessRight, Database *database, QWidget *parent) : QWidget(parent),
    userFileSystemView(systemAccessRight, database),
    matrixesWidget(database) {
    userFileSystemView.show();
    matrixesWidget.show();
    hide();
}


Widget::~Widget() {

}

