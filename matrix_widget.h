#ifndef MATRIX_WIDGET_H
#define MATRIX_WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include "database.h"

class MatrixWidget : public QTableWidget {
    Q_OBJECT
public:
    MatrixWidget(Database *db, QWidget *parent = nullptr);

public slots:
    virtual void updateValues() = 0;

private slots:
    virtual void setValue(QModelIndex index) = 0;

protected:
    Database *database;
};

#endif // MATRIX_WIDGET_H
