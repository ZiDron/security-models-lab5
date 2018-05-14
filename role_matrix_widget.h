#ifndef ROLE_MATRIX_WIDGET_H
#define ROLE_MATRIX_WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include "matrix_widget.h"
#include "database.h"

class RoleMatrixWidget : public MatrixWidget {
    Q_OBJECT
public:
    RoleMatrixWidget(Database *db, QWidget *parent = nullptr);

public slots:
    void updateValues();

private slots:
    void setValue(QModelIndex index);
};

#endif // ROLE_MATRIX_WIDGET_H
