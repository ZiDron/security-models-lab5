#include "access_right_matrix_widget.h"

AccessRightMatrixWidget::AccessRightMatrixWidget(Database *db, QWidget *parent) : MatrixWidget(db, parent) {
    updateValues();
}

void AccessRightMatrixWidget::updateValues() {
    clear();
    QList<AccessRight*> rights = database->getRightsList();
    QStringList rightsNames = database->getRightsNameList();
    QList<Role*> roles = database->getRoleList();
    QStringList rolesNames = database->getRoleNameList();
    setColumnCount(rights.count());
    setHorizontalHeaderLabels(rightsNames);
    setRowCount(roles.count());
    setVerticalHeaderLabels(rolesNames);
    resizeColumnsToContents();

    for (int u = 0; u < roles.count(); u++) {
        Role* role = roles.at(u);
        QList<AccessRight*>* rolesRights = role->getPermisions();
        for (int r = 0; r < rolesRights->count(); r++) {
            int index = rightsNames.indexOf(rolesRights->at(r)->getName());
            if (index > 0) {
                QTableWidgetItem* item = new QTableWidgetItem(QString("+"));
                item->setTextAlignment(Qt::AlignCenter);
                setItem(u, index, item);
            }
            QTableWidgetItem* item = new QTableWidgetItem(QString("+"));
            item->setTextAlignment(Qt::AlignCenter);
            setItem(u, 0, item);
        }
    }
}

void AccessRightMatrixWidget::setValue(QModelIndex index) {
    database->changeRole(database->getRoleList().at(index.row())->getName(),
                         database->getRightsList().at(index.column())->getName(),
                         (index.data().toString() == "+") ? Database::Remove : Database::Add);
}
