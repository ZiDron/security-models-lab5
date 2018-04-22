#ifndef ROLE_MATRIX_WIDGET_H
#define ROLE_MATRIX_WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include "database.h"

class RoleMatrixWidget : public QTableWidget {
    Q_OBJECT
public:
    explicit RoleMatrixWidget(Database *db, QWidget *parent = nullptr);

signals:

public slots:

    void updateValues();
private slots:
    void setValue(QModelIndex index);

private:
    Database *database;
};

#endif // ROLE_MATRIX_WIDGET_H
