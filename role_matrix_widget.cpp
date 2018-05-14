#include "role_matrix_widget.h"

RoleMatrixWidget::RoleMatrixWidget(Database *db, QWidget *parent) : MatrixWidget(db, parent) {
    updateValues();
}

void RoleMatrixWidget::setValue(QModelIndex index) {
    database->changeUser(database->getUsersList().at(index.row())->getName(),
                         database->getRoleList().at(index.column())->getName(),
                         (index.data().toString() == "+") ? Database::Remove : Database::Add);
}

void RoleMatrixWidget::updateValues() {
    clear();
    QList<Role*> roles = database->getRoleList();
    QStringList rolesNames = database->getRoleNameList();
    QList<User*> users = database->getUsersList();
    QStringList usersNames = database->getUsersNameList();
    setColumnCount(roles.count());
    setHorizontalHeaderLabels(rolesNames);
    setRowCount(users.count());
    setVerticalHeaderLabels(usersNames);
    resizeColumnsToContents();

    for (int u = 0; u < users.count(); u++) {
        User* user = users.at(u);
        QList<Role*>* userRoles = user->getRole();
        for (int r = 0; r < userRoles->count(); r++) {
            int index = rolesNames.indexOf(userRoles->at(r)->getName());
            if (index >= 0) {
                QTableWidgetItem* item = new QTableWidgetItem(QString("+"));
                item->setTextAlignment(Qt::AlignCenter);
                setItem(u, index, item);
            }
        }
    }
}
