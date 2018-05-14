#include "create_items_widget.h"

CreateItemsWidget::CreateItemsWidget(Database *db, QWidget *parent) : QWidget(),
    userCreateButton(QString("Create User")),
    roleCreateButton(QString("Create Role")),
    accessRightCreateButton(QString("Create Right")),
    mainLayout(this) {
    mainLayout.setContentsMargins(0, 0, 0, 0);
    mainLayout.setSpacing(0);

    userNameLineEdit.setPlaceholderText(QString("Enter User name"));
    roleNameLineEdit.setPlaceholderText(QString("Enter Role name"));
    accessRightNameLineEdit.setPlaceholderText(QString("Enter Right name"));

    connect(&userCreateButton, SIGNAL(released()), this, SLOT(userCreateSlot()));
    connect(&roleCreateButton, SIGNAL(released()), this, SLOT(roleCreateSlot()));
    connect(&accessRightCreateButton, SIGNAL(released()), this, SLOT(accessRightCreateSlot()));
}

void CreateItemsWidget::userCreateSlot() {

}

void CreateItemsWidget::roleCreateSlot() {

}

void CreateItemsWidget::accessRightCreateSlot() {

}
