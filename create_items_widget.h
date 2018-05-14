#ifndef CREATE_ITEMS_WIDGET_H
#define CREATE_ITEMS_WIDGET_H

#include <QWidget>
#include "database.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

class CreateItemsWidget : public QWidget {
public:
    CreateItemsWidget(Database *db, QWidget *parent = 0);

private:
    QVBoxLayout mainLayout;
    QLineEdit userNameLineEdit;
    QPushButton userCreateButton;

    QLineEdit roleNameLineEdit;
    QPushButton roleCreateButton;

    QLineEdit accessRightNameLineEdit;
    QPushButton accessRightCreateButton;

public slots:
    void userCreateSlot();
    void roleCreateSlot();
    void accessRightCreateSlot();
};

#endif // CREATE_ITEMS_WIDGET_H
