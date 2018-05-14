#include "matrixes_widget.h"

MatrixesWidget::MatrixesWidget(Database *database, QWidget *parent) : QWidget(parent),
    roleMatrix(database, this),
    accessRightMatrix(database, this),
    mainLayout(this) {
    mainLayout.setContentsMargins(0, 0, 0, 0);
    mainLayout.setSpacing(0);
    splitter.addWidget(&roleMatrix);
    splitter.addWidget(&accessRightMatrix);
    mainLayout.addWidget(&splitter, 10);
    setMinimumSize(1000, 600);
}
