#ifndef CREATE_ITEMS_WIDGET_H
#define CREATE_ITEMS_WIDGET_H

#include <QWidget>
#include "database.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QShortcut>

class CreateItemsWidget : public QWidget {
    Q_OBJECT

public:
    CreateItemsWidget(Database *db, QWidget *parent = 0);

private:
    QGridLayout mainLayout;
    QLineEdit userNameLineEdit;
    QPushButton userCreateButton;
    QPushButton userRemoveButton;

    QLineEdit roleNameLineEdit;
    QPushButton roleCreateButton;
    QPushButton roleRemoveButton;

    QLineEdit accessRightNameLineEdit;
    QPushButton accessRightCreateButton;
    QSpinBox accessRightLevelSpinBox;
    QPushButton accessRightRemoveButton;

    Database *database;

public slots:
    void userCreateSlot();
    void roleCreateSlot();
    void accessRightCreateSlot();
    void userRemoveSlot();
    void roleRemoveSlot();
    void accessRightRemoveSlot();
};

#endif // CREATE_ITEMS_WIDGET_H
