#include "role_matrix_widget.h"

RoleMatrixWidget::RoleMatrixWidget(Database *db, QWidget *parent) : QTableWidget(db->getUsersList().count(), db->getRoleList().count(), parent) {
    database = db;
    setSelectionMode(QAbstractItemView::NoSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(setValue(QModelIndex)));
}

void RoleMatrixWidget::setValue(QModelIndex index) {
//    database->angeRule(matrix->getUsersList().at(index.row()),
//                       matrix->getAlphabet()[index.column()],
//            (index.data().toString() == "+") ? '0' : '1');
}

void RoleMatrixWidget::updateValues() {
//    table.clear();

//    QString alphabet = matrix->getAlphabet();
//    QStringList names = matrix->getUsersList();
//    QStringList header;
//    for (int i = 0; i < alphabet.length(); i++) {
//        header.append(alphabet.at(i));
//    }
//    table.setColumnCount(header.count());
//    table.setHorizontalHeaderLabels(header);
//    table.setRowCount(names.count());
//    table.setVerticalHeaderLabels(names);
//    table.resizeColumnsToContents();

//    for (int n = 0; n < names.count(); n++) {
//        QString rule = matrix->findUserRules(names.at(n));
//        for (int a = 0; a < header.count(); a++) {
//            QTableWidgetItem* item = new QTableWidgetItem((rule[a] == '1') ? QString("+") : QString(""));
//            item->setTextAlignment(Qt::AlignCenter);
//            table.setItem(n, a, item);
//        }
//    }

//    updateComboBox(&userComboBox, names);
//    updateComboBox(&removeComboBox, names);
//    updateComboBox(&grantFromComboBox, names);
//    updateComboBox(&grantToComboBox, names);
}

