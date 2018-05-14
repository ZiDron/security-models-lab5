#include "matrix_widget.h"

MatrixWidget::MatrixWidget(Database *db, QWidget *parent) : QTableWidget(parent) {
    database = db;
    setSelectionMode(QAbstractItemView::NoSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(setValue(QModelIndex)));
    connect(db, SIGNAL(updated()), this, SLOT(updateValues()));
}
