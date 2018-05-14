#ifndef ACCESS_RIGHT_MATRIX_WIDGET_H
#define ACCESS_RIGHT_MATRIX_WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include "matrix_widget.h"
#include "database.h"

class AccessRightMatrixWidget : public MatrixWidget {
    Q_OBJECT
public:
    AccessRightMatrixWidget(Database *db, QWidget *parent = nullptr);

public slots:
    void updateValues();

private slots:
    void setValue(QModelIndex index);
};

#endif // ACCESS_RIGHT_MATRIX_WIDGET_H
