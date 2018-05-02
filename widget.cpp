#include "widget.h"

Widget::Widget(SystemAccessRight *systemAccessRight, Database *database, QWidget *parent)
    : QWidget(parent),
      userFileSystemView(systemAccessRight, database, this),
      roleMatrix(database) {
    roleMatrix.show();
}


Widget::~Widget() {

}

