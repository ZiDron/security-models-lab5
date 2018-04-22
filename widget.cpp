#include "widget.h"

Widget::Widget(SystemAccessRight *systemAccessRight, Database *database, QWidget *parent)
    : QWidget(parent),
      mainLayout(this),
      splitter(this),
      treeViewLeft(this),
      treeViewRight(this),
      currentUserComboBox(this) {
    this->systemAccessRight = systemAccessRight;
    this->database = database;
    pathLineEditLeft.setReadOnly(1);
    pathLineEditRight.setReadOnly(1);
    modelLeft = new FileSystemPermissionModel(database);
    modelRight = new FileSystemPermissionModel(database);
    modelLeft->setFilter(QDir::AllEntries | QDir::NoDot);
    modelRight->setFilter(QDir::AllEntries | QDir::NoDot);
    modelLeft->setRootPath(QString("/"));
    modelRight->setRootPath(QString("/"));
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
    treeViewLeft.setModel(modelLeft);
    treeViewRight.setModel(modelRight);
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

    editPuttonsLayout.setContentsMargins(0, 0, 0, 0);
    editPuttonsLayout.setSpacing(0);
    for (int i = 0; i < 7; i++) {
        QPushButton *btn = new QPushButton(QString("Button %1").arg(i + 1), this);
        btn->setFlat(1);
        editPuttonsLayout.addWidget(btn);
        QFrame *line = new QFrame(this);
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Raised);
        editPuttonsLayout.addWidget(line);
        if (i == 2) {
            copyButton = btn;
        }
        if (i == 3) {
            nonSecretButton = btn;
        }
        if (i == 4) {
            secretButton = btn;
        }
        if (i == 5) {
            topSecretButton = btn;
        }
        if (i == 6) {
            mkdirButton = btn;
        }

    }


    currentUserComboBox.addItems(database->getUsersList());

    editPuttonsLayout.addWidget(&currentUserComboBox);

    copyButton->setText(QString("Copy F5"));
    copyButton->setShortcut(QKeySequence(Qt::Key_F5));
    connect(copyButton, SIGNAL(released()), this, SLOT(copyButtonClickedSlot()));

    nonSecretButton->setText(QString("Non Secret F6"));
    nonSecretButton->setShortcut(QKeySequence(Qt::Key_F6));
    connect(nonSecretButton, SIGNAL(released()), this, SLOT(setNonSecretSlot()));

    secretButton->setText(QString("Secret F7"));
    secretButton->setShortcut(QKeySequence(Qt::Key_F7));
    connect(secretButton, SIGNAL(released()), this, SLOT(setSecretSlot()));

    topSecretButton->setText(QString("Top Secret F8"));
    topSecretButton->setShortcut(QKeySequence(Qt::Key_F8));
    connect(topSecretButton, SIGNAL(released()), this, SLOT(setTopSecretSlot()));

    splitter.addWidget(leftArea);
    splitter.addWidget(rightArea);
    mainLayout.setContentsMargins(0, 0, 0, 0);
    mainLayout.setSpacing(0);
    mainLayout.addWidget(&splitter, 1);
    mainLayout.addLayout(&editPuttonsLayout);

    connect(&treeViewLeft, SIGNAL(clicked(QModelIndex)), this, SLOT(leftTreeViewActivatedSlot(QModelIndex)));
    connect(&treeViewRight, SIGNAL(clicked(QModelIndex)), this, SLOT(rightTreeViewActivatedSlot(QModelIndex)));
    connect(&treeViewLeft, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(leftTreeViewClickedSlot(QModelIndex)));
    connect(&treeViewRight, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(rightTreeViewClickedSlot(QModelIndex)));
    setMinimumSize(1000, 600);
}


Widget::~Widget() {

}

void Widget::copyButtonClickedSlot() {
    FileSystemPermissionModel *model = dynamic_cast<FileSystemPermissionModel*>(focusTreeView->model());
    QString source = model->filePath(focusTreeView->currentIndex());
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

void Widget::setNonSecretSlot() {
    FileSystemPermissionModel *model = dynamic_cast<FileSystemPermissionModel*>(focusTreeView->model());
    if (model) {
        QList<QString> list = database->getRightsList();
        database->changeRight(model->filePath(focusTreeView->currentIndex()), list[0]/*SystemAccessRight::NonSecret*/);
        focusTreeView->update(focusTreeView->currentIndex());
    }
}

void Widget::setSecretSlot() {
    FileSystemPermissionModel *model = dynamic_cast<FileSystemPermissionModel*>(focusTreeView->model());
    if (model) {
        QList<QString> list = database->getRightsList();
        database->changeRight(model->filePath(focusTreeView->currentIndex()), list[1]/*SystemAccessRight::Secret*/);
        focusTreeView->update(focusTreeView->currentIndex());
    }
}

void Widget::setTopSecretSlot() {
    FileSystemPermissionModel *model = dynamic_cast<FileSystemPermissionModel*>(focusTreeView->model());
    if (model) {
        QList<QString> list = database->getRightsList();
        database->changeRight(model->filePath(focusTreeView->currentIndex()), list[2]/*SystemAccessRight::TopSecret*/);
        focusTreeView->update(focusTreeView->currentIndex());
    }
}

void Widget::leftUpSlot() {
    QDir dir(pathLineEditLeft.text());
    if (dir.cdUp()) {
        pathLineEditLeft.setText(dir.absolutePath());
        modelLeft->setRootPath(dir.absolutePath());
        treeViewLeft.setRootIndex(modelLeft->index(dir.absolutePath()));
    }
}

void Widget::rightUpSlot() {
    QDir dir(pathLineEditRight.text());
    if (dir.cdUp()) {
        pathLineEditRight.setText(dir.absolutePath());
        modelRight->setRootPath(dir.absolutePath());
        treeViewRight.setRootIndex(modelRight->index(dir.absolutePath()));
    }
}

void Widget::leftTreeViewClickedSlot(QModelIndex index) {
    QDir dir(pathLineEditLeft.text());
    if (index.data().toString() == QString("..")) {
        if (dir.cdUp()) {
            treeViewLeft.setRootIndex(modelLeft->index(dir.absolutePath()));
        }
    } else {
        if (dir.cd(index.data().toString())) {
            treeViewLeft.setRootIndex(index);
        }
    }
    pathLineEditLeft.setText(dir.absolutePath());
    modelLeft->setRootPath(dir.absolutePath());
    treeViewLeft.setModel(modelLeft);
    treeViewRight.clearSelection();
}

void Widget::rightTreeViewClickedSlot(QModelIndex index) {
    QDir dir(pathLineEditRight.text());
    if (index.data().toString() == QString("..")) {
        if (dir.cdUp()) {
            treeViewRight.setRootIndex(modelRight->index(dir.absolutePath()));
        }
    } else if (dir.cd(index.data().toString())) {
        treeViewRight.setRootIndex(index);
    }
    pathLineEditRight.setText(dir.absolutePath());
    modelRight->setRootPath(dir.absolutePath());
    treeViewRight.setModel(modelRight);
    treeViewLeft.clearSelection();
}

void Widget::leftTreeViewActivatedSlot(QModelIndex index) {
    focusTreeView = &treeViewLeft;
    treeViewRight.clearSelection();
}

void Widget::rightTreeViewActivatedSlot(QModelIndex index) {
    focusTreeView = &treeViewRight;
    treeViewLeft.clearSelection();
}
