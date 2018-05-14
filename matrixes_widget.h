#ifndef MATRIXES_WIDGET_H
#define MATRIXES_WIDGET_H

#include "database.h"
#include "role_matrix_widget.h"
#include "access_right_matrix_widget.h"
#include <QVBoxLayout>
#include <QSplitter>

class MatrixesWidget : public QWidget {
    Q_OBJECT

public:
    MatrixesWidget(Database *database, QWidget *parent = 0);

private:
    RoleMatrixWidget roleMatrix;
    AccessRightMatrixWidget accessRightMatrix;

    QVBoxLayout mainLayout;
    QSplitter splitter;
};

#endif // MATRIXES_WIDGET_H
