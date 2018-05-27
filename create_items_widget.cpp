#include "create_items_widget.h"

CreateItemsWidget::CreateItemsWidget(Database *db, QWidget *parent) : QWidget(),
    database(db),
    userCreateButton(QString("Create User")),
    roleCreateButton(QString("Create Role")),
    accessRightCreateButton(QString("Create Right")),
    userRemoveButton(QString("Remove User")),
    roleRemoveButton(QString("Remove Role")),
    accessRightRemoveButton(QString("Remove Right")),
    mainLayout(this) {
    mainLayout.setContentsMargins(0, 0, 0, 0);
    mainLayout.setSpacing(0);

    mainLayout.addWidget(&userNameLineEdit, 0, 0, 1, 2);
    mainLayout.addWidget(&userCreateButton, 0, 3, 1, 1);
    mainLayout.addWidget(&userRemoveButton, 0, 4, 1, 1);

    mainLayout.addWidget(&roleNameLineEdit, 1, 0, 1, 2);
    mainLayout.addWidget(&roleCreateButton, 1, 3, 1, 1);
    mainLayout.addWidget(&roleRemoveButton, 1, 4, 1, 1);

    mainLayout.addWidget(&accessRightNameLineEdit, 2, 0, 1, 1);
//    mainLayout.addWidget(&accessRightLevelSpinBox, 2, 1, 1, 1);
    mainLayout.addWidget(&accessRightCreateButton, 2, 3, 1, 1);
    mainLayout.addWidget(&accessRightRemoveButton, 2, 4, 1, 1);

    userNameLineEdit.setPlaceholderText(QString("Enter User name"));
    roleNameLineEdit.setPlaceholderText(QString("Enter Role name"));
    accessRightNameLineEdit.setPlaceholderText(QString("Enter Right name"));

    userCreateButton.setFlat(true);
    roleCreateButton.setFlat(true);
    accessRightCreateButton.setFlat(true);
    userRemoveButton.setFlat(true);
    roleRemoveButton.setFlat(true);
    accessRightRemoveButton.setFlat(true);



    connect(&userCreateButton, SIGNAL(released()), this, SLOT(userCreateSlot()));
    connect(&roleCreateButton, SIGNAL(released()), this, SLOT(roleCreateSlot()));
    connect(&accessRightCreateButton, SIGNAL(released()), this, SLOT(accessRightCreateSlot()));
    connect(&userRemoveButton, SIGNAL(released()), this, SLOT(userRemoveSlot()));
    connect(&roleRemoveButton, SIGNAL(released()), this, SLOT(roleRemoveSlot()));
    connect(&accessRightRemoveButton, SIGNAL(released()), this, SLOT(accessRightRemoveSlot()));
    setMinimumWidth(400);
}

void CreateItemsWidget::userCreateSlot() {
    if (database->createNewUser(userNameLineEdit.text())) {
        userNameLineEdit.clear();
    }
}

void CreateItemsWidget::roleCreateSlot() {
    if (database->createNewRole(roleNameLineEdit.text())) {
        roleNameLineEdit.clear();
    }
}

void CreateItemsWidget::accessRightCreateSlot() {
    if (database->createNewRight(accessRightNameLineEdit.text(), database->getHighestRight()->getLevel() + 1)) {
        accessRightNameLineEdit.clear();
        accessRightLevelSpinBox.setValue(0);
    }
}

void CreateItemsWidget::userRemoveSlot() {
    if (database->removeUser(userNameLineEdit.text())) {
        userNameLineEdit.clear();
    }
}

void CreateItemsWidget::roleRemoveSlot() {
    if (database->removeRole(roleNameLineEdit.text())) {
        roleNameLineEdit.clear();
    }
}

void CreateItemsWidget::accessRightRemoveSlot() {
    if (database->removeRight(accessRightNameLineEdit.text())) {
        accessRightNameLineEdit.clear();
        accessRightLevelSpinBox.setValue(0);
    }
}
