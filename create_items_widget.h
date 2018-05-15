#ifndef CREATE_ITEMS_WIDGET_H
#define CREATE_ITEMS_WIDGET_H

#include <QWidget>
#include "database.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>

class CreateItemsWidget : public QWidget {
    Q_OBJECT

public:
    CreateItemsWidget(Database *db, QWidget *parent = 0);

private:
    QGridLayout mainLayout;
    QLineEdit userNameLineEdit;
    QPushButton userCreateButton;

    QLineEdit roleNameLineEdit;
    QPushButton roleCreateButton;

    QLineEdit accessRightNameLineEdit;
    QPushButton accessRightCreateButton;
    QSpinBox accessRightLevelSpinBox;

    Database *database;

public slots:
    void userCreateSlot();
    void roleCreateSlot();
    void accessRightCreateSlot();
};

#endif // CREATE_ITEMS_WIDGET_H
