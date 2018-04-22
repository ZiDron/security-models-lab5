#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTreeView>
#include <QFileSystemModel>
#include <QSplitter>
#include <QHeaderView>
#include "system_access_right.h"
#include "file_system_permission_model.h"
#include "database.h"
#include <QMessageBox>
#include <QDialog>
#include <QComboBox>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(SystemAccessRight *systemAccessRight,
           Database *database,
           QWidget *parent = 0);
    ~Widget();

private:
    SystemAccessRight *systemAccessRight;
    Database *database;
    QVBoxLayout mainLayout;
    QHBoxLayout editPuttonsLayout;
    QSplitter splitter;
    QLineEdit pathLineEditLeft;
    QLineEdit pathLineEditRight;
    QTreeView treeViewLeft;
    QTreeView treeViewRight;
    QTreeView* focusTreeView;
    FileSystemPermissionModel *modelLeft;
    FileSystemPermissionModel *modelRight;
    QPushButton *copyButton;
    QPushButton *nonSecretButton;
    QPushButton *secretButton;
    QPushButton *topSecretButton;
    QPushButton *mkdirButton;
    QComboBox currentUserComboBox;

public slots:
    void copyButtonClickedSlot();
    void setNonSecretSlot();
    void setSecretSlot();
    void setTopSecretSlot();

private slots:
    void leftUpSlot();
    void rightUpSlot();
    void leftTreeViewClickedSlot(QModelIndex index);
    void rightTreeViewClickedSlot(QModelIndex index);
    void leftTreeViewActivatedSlot(QModelIndex index);
    void rightTreeViewActivatedSlot(QModelIndex index);
};

#endif // WIDGET_H
