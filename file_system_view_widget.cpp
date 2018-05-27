#include "file_system_view_widget.h"

FileSystemViewWidget::FileSystemViewWidget(SystemAccessRight *systemAccessRight, Database *database, QWidget *parent) : QWidget(parent),
    mainLayout(this),
    splitter(this),
    treeViewLeft(this),
    treeViewRight(this) {
    this->systemAccessRight = systemAccessRight;
    this->database = database;
    state = UserControl;
    buttonsWidget.setLayout(&editButtonsLayout);

    pathLineEditLeft.setReadOnly(1);
    pathLineEditRight.setReadOnly(1);
    modelLeft = new FileSystemPermissionModel(database);
    modelRight = new FileSystemPermissionModel(database);
    filterModelLeft = new PermissionFilterModel(database);
    filterModelRight = new PermissionFilterModel(database);
    modelLeft->setFilter(QDir::AllEntries | QDir::NoDot);
    modelRight->setFilter(QDir::AllEntries | QDir::NoDot);
    modelLeft->setRootPath(QString("/"));
    modelRight->setRootPath(QString("/"));
    filterModelLeft->setSourceModel(modelLeft);
    filterModelRight->setSourceModel(modelRight);
    treeViewLeft.setAllColumnsShowFocus(1);
    treeViewLeft.setExpandsOnDoubleClick(0);
    treeViewLeft.setItemsExpandable(0);
    treeViewLeft.setUniformRowHeights(1);
    treeViewRight.setAllColumnsShowFocus(1);
    treeViewRight.setExpandsOnDoubleClick(0);
    treeViewRight.setItemsExpandable(0);
    treeViewRight.setUniformRowHeights(1);
    treeViewLeft.setSelectionBehavior(QAbstractItemView::SelectRows);
    treeViewRight.setSelectionBehavior(QAbstractItemView::SelectRows);
    treeViewLeft.setModel(filterModelLeft);
    treeViewRight.setModel(filterModelRight);
    treeViewLeft.setRootIsDecorated(0);
    treeViewRight.setRootIsDecorated(0);
    treeViewLeft.header()->setStretchLastSection(0);
    treeViewRight.header()->setStretchLastSection(0);

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    treeViewLeft.header()->setResizeMode(0, QHeaderView::Stretch);
    treeViewRight.header()->setResizeMode(0, QHeaderView::Stretch);
#else
    treeViewLeft.header()->setSectionResizeMode(0, QHeaderView::Stretch);
    treeViewRight.header()->setSectionResizeMode(0, QHeaderView::Stretch);
#endif

    QWidget *leftArea = new QWidget(this);
    QVBoxLayout *leftAreaLayout = new QVBoxLayout(leftArea);
    leftAreaLayout->setContentsMargins(0, 0, 0, 0);
    leftAreaLayout->setSpacing(0);
    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->setContentsMargins(0, 0, 0, 0);
    topLeftLayout->setSpacing(0);
    topLeftLayout->addWidget(&pathLineEditLeft, 10);
    QPushButton *leftUpButton = new QPushButton(QString(QChar(0x2191)), this);
    leftUpButton->setMaximumWidth(30);
    topLeftLayout->addWidget(leftUpButton);
    connect(leftUpButton, SIGNAL(released()), this, SLOT(leftUpSlot()));
    leftAreaLayout->addLayout(topLeftLayout, 0);
    leftAreaLayout->addWidget(&treeViewLeft, 10);

    QWidget *rightArea = new QWidget(this);
    QVBoxLayout *rightAreaLayout = new QVBoxLayout(rightArea);
    rightAreaLayout->setContentsMargins(0, 0, 0, 0);
    rightAreaLayout->setSpacing(0);
    QHBoxLayout *topRightLayout = new QHBoxLayout;
    topRightLayout->setContentsMargins(0, 0, 0, 0);
    topRightLayout->setSpacing(0);
    topRightLayout->addWidget(&pathLineEditRight, 10);
    QPushButton *rightUpButton = new QPushButton(QString(QChar(0x2191)), this);
    rightUpButton->setMaximumWidth(30);
    topRightLayout->addWidget(rightUpButton);
    connect(rightUpButton, SIGNAL(released()), this, SLOT(rightUpSlot()));
    rightAreaLayout->addLayout(topRightLayout, 0);

    rightAreaLayout->addWidget(&treeViewRight, 10);

    editButtonsLayout.setContentsMargins(0, 0, 0, 0);
    editButtonsLayout.setSpacing(0);

    updateButtons();

    QShortcut *shortCut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_L), this, SLOT(changeAdminControls()));

    splitter.addWidget(leftArea);
    splitter.addWidget(rightArea);
    mainLayout.setContentsMargins(0, 0, 0, 0);
    mainLayout.setSpacing(0);
    mainLayout.addWidget(&splitter, 1);
    mainLayout.addWidget(&buttonsWidget);

    connect(&mapper, SIGNAL(mapped(QString)), this, SLOT(changePathRight(QString)));
    connect(database, SIGNAL(updated()), this, SLOT(updateButtons()));
    connect(&treeViewLeft, SIGNAL(clicked(QModelIndex)), this, SLOT(leftTreeViewActivatedSlot(QModelIndex)));
    connect(&treeViewRight, SIGNAL(clicked(QModelIndex)), this, SLOT(rightTreeViewActivatedSlot(QModelIndex)));
    connect(&treeViewLeft, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(leftTreeViewClickedSlot(QModelIndex)));
    connect(&treeViewRight, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(rightTreeViewClickedSlot(QModelIndex)));
    buttonsWidget.hide();

    setMinimumSize(900, 600);
}

void FileSystemViewWidget::copyButtonClickedSlot() {
    PermissionFilterModel *filter = dynamic_cast<PermissionFilterModel*>(focusTreeView->model());
    FileSystemPermissionModel *sourceModel = dynamic_cast<FileSystemPermissionModel*>(filter->sourceModel());
    QString source = sourceModel->filePath(filter->mapToSource(focusTreeView->currentIndex()));
    QString destination;
    if (focusTreeView == &treeViewLeft) {
        destination = pathLineEditRight.text();
    } else {
        destination = pathLineEditLeft.text();
    }
    if (!systemAccessRight->copy(source, destination)){
        QMessageBox::critical(this, QString("Permission Error!"), QString("Operation not permitted!"));
    };
}

void FileSystemViewWidget::leftUpSlot() {
    QDir dir(pathLineEditLeft.text());
    if (dir.cdUp()) {
        pathLineEditLeft.setText(dir.absolutePath());
        modelLeft->setRootPath(dir.absolutePath());
        treeViewLeft.setRootIndex(filterModelLeft->mapFromSource(modelLeft->index(dir.absolutePath())));
    }
}

void FileSystemViewWidget::rightUpSlot() {
    QDir dir(pathLineEditRight.text());
    if (dir.cdUp()) {
        pathLineEditRight.setText(dir.absolutePath());
        modelRight->setRootPath(dir.absolutePath());
        treeViewRight.setRootIndex(filterModelRight->mapFromSource(modelRight->index(dir.absolutePath())));
    }
}

void FileSystemViewWidget::leftTreeViewClickedSlot(QModelIndex index) {
    QDir dir(pathLineEditLeft.text());
    if (index.data().toString() == QString("..")) {
        if (dir.cdUp()) {
            treeViewLeft.setRootIndex(filterModelLeft->mapFromSource(modelLeft->index(dir.absolutePath())));
        }
    } else {
        if (dir.cd(index.data().toString())) {
            treeViewLeft.setRootIndex(index);
        }
    }
    pathLineEditLeft.setText(dir.absolutePath());
    modelLeft->setRootPath(dir.absolutePath());
    treeViewLeft.setModel(filterModelLeft);
    treeViewRight.clearSelection();
}

void FileSystemViewWidget::rightTreeViewClickedSlot(QModelIndex index) {
    QDir dir(pathLineEditRight.text());
    if (index.data().toString() == QString("..")) {
        if (dir.cdUp()) {
            treeViewRight.setRootIndex(filterModelRight->mapFromSource(modelRight->index(dir.absolutePath())));
        }
    } else if (dir.cd(index.data().toString())) {
        treeViewRight.setRootIndex(index);
    }
    pathLineEditRight.setText(dir.absolutePath());
    modelRight->setRootPath(dir.absolutePath());
    treeViewRight.setModel(filterModelRight);
    treeViewLeft.clearSelection();
}

void FileSystemViewWidget::leftTreeViewActivatedSlot(QModelIndex index) {
    focusTreeView = &treeViewLeft;
    treeViewRight.clearSelection();
}

void FileSystemViewWidget::rightTreeViewActivatedSlot(QModelIndex index) {
    focusTreeView = &treeViewRight;
    treeViewLeft.clearSelection();
}

void FileSystemViewWidget::userChosenSlot(int index) {
    User* user = database->getUsersList().at(index);
    filterModelLeft->setUser(user);
    filterModelRight->setUser(user);
    filterModelLeft->invalidate();
    filterModelRight->invalidate();
}

void FileSystemViewWidget::changeAdminControls() {
    state = (ControlState)!state;
    if (state == UserControl) {
        buttonsWidget.hide();
    }
    if (state == AdministratorControl) {
        buttonsWidget.show();
    }
}

void FileSystemViewWidget::updateButtons() {
    clearLayout(&editButtonsLayout, true);
    QList<AccessRight*> list = database->getRightsList();

    copyButton = new QPushButton(("F5 Copy"));
    copyButton->setFlat(1);
    copyButton->setShortcut(QKeySequence(Qt::Key_F5));
    connect(copyButton, SIGNAL(released()), this, SLOT(copyButtonClickedSlot()));
    editButtonsLayout.addWidget(copyButton);

    for (int i = 0; i < list.count(); i++) {
        QPushButton *btn = new QPushButton(QString("F%1 %2").arg(i + 1).arg(list.at(i)->getName()), this);
        btn->setFlat(1);
        editButtonsLayout.addWidget(btn);
        QFrame *line = new QFrame(this);
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Raised);
        editButtonsLayout.addWidget(line);
        mapper.setMapping(btn, list.at(i)->getName());
        connect(btn, SIGNAL(clicked()), &mapper, SLOT(map()));
    }
    currentUserComboBox = new QComboBox;
    currentUserComboBox->addItems(database->getUsersNameList());
    connect(currentUserComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(userChosenSlot(int)));
    editButtonsLayout.addWidget(currentUserComboBox);
}

void FileSystemViewWidget::clearLayout(QLayout *layout, bool deleteWidgets) {
    while (QLayoutItem* item = layout->takeAt(0)) {
        if (deleteWidgets) {
            if (QWidget* widget = item->widget()) {
                widget->deleteLater();
            }
            if (QLayout* childLayout = item->layout()) {
                clearLayout(childLayout, deleteWidgets);
            }
            delete item;
        }
    }
}

void FileSystemViewWidget::changePathRight(QString right) {
    PermissionFilterModel *filter = dynamic_cast<PermissionFilterModel*>(focusTreeView->model());
    if (filter) {
        FileSystemPermissionModel *source = dynamic_cast<FileSystemPermissionModel*>(filter->sourceModel());
        if (source) {
            QList<QString> list = database->getRightsNameList();
            database->changeRight(source->filePath(filter->mapToSource(focusTreeView->currentIndex())), right);
            filter->invalidate();
//            focusTreeView->update(focusTreeView->currentIndex());
        }
    }
}
