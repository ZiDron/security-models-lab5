#include "widget.h"

Widget::Widget(SystemAccessRight *systemAccessRight, Database *database, QWidget *parent) : QWidget(parent),
    userFileSystemView(systemAccessRight, database),
    roleMatrix(database),
    accessRightMatrix(database) {
    userFileSystemView.show();
    roleMatrix.show();
    accessRightMatrix.show();
    hide();
}


Widget::~Widget() {

}

