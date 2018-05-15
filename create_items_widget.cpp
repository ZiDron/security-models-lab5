#include "create_items_widget.h"

CreateItemsWidget::CreateItemsWidget(Database *db, QWidget *parent) : QWidget(),
    database(db),
    userCreateButton(QString("Create User")),
    roleCreateButton(QString("Create Role")),
    accessRightCreateButton(QString("Create Right")),
    mainLayout(this) {
    mainLayout.setContentsMargins(0, 0, 0, 0);
    mainLayout.setSpacing(0);

    mainLayout.addWidget(&userNameLineEdit, 0, 0, 1, 2);
    mainLayout.addWidget(&roleNameLineEdit, 1, 0, 1, 2);
    mainLayout.addWidget(&accessRightNameLineEdit, 2, 0, 1, 1);
    mainLayout.addWidget(&accessRightLevelSpinBox, 2, 1, 1, 1);
    mainLayout.addWidget(&userCreateButton, 0, 3, 1, 1);
    mainLayout.addWidget(&roleCreateButton, 1, 3, 1, 1);
    mainLayout.addWidget(&accessRightCreateButton, 2, 3, 1, 1);

    userNameLineEdit.setPlaceholderText(QString("Enter User name"));
    roleNameLineEdit.setPlaceholderText(QString("Enter Role name"));
    accessRightNameLineEdit.setPlaceholderText(QString("Enter Right name"));

    connect(&userCreateButton, SIGNAL(released()), this, SLOT(userCreateSlot()));
    connect(&roleCreateButton, SIGNAL(released()), this, SLOT(roleCreateSlot()));
    connect(&accessRightCreateButton, SIGNAL(released()), this, SLOT(accessRightCreateSlot()));
}

void CreateItemsWidget::userCreateSlot() {
    database->createNewUser(userNameLineEdit.text());
    userNameLineEdit.clear();
}

void CreateItemsWidget::roleCreateSlot() {
    database->createNewRole(roleNameLineEdit.text());
    roleNameLineEdit.clear();
}

void CreateItemsWidget::accessRightCreateSlot() {
    database->createNewRight(accessRightNameLineEdit.text(), accessRightLevelSpinBox.value());
    accessRightNameLineEdit.clear();
    accessRightLevelSpinBox.setValue(0);
}
