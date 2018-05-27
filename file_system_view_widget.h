#ifndef FILE_SYSTEM_VIEW_WIDGET_H
#define FILE_SYSTEM_VIEW_WIDGET_H

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
#include "permission_filter_model.h"
#include "database.h"
#include <QMessageBox>
#include <QDialog>
#include <QComboBox>
#include <QSignalMapper>
#include <QShortcut>

class FileSystemViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FileSystemViewWidget(SystemAccessRight *systemAccessRight, Database *database, QWidget *parent = nullptr);

public:
    enum ControlState {
        AdministratorControl = 0,
        UserControl = 1
    };

private:
    SystemAccessRight *systemAccessRight;
    Database *database;
    QVBoxLayout mainLayout;
    QHBoxLayout editButtonsLayout;
    QSplitter splitter;
    QLineEdit pathLineEditLeft;
    QLineEdit pathLineEditRight;
    QTreeView treeViewLeft;
    QTreeView treeViewRight;
    QTreeView* focusTreeView;
    FileSystemPermissionModel *modelLeft;
    FileSystemPermissionModel *modelRight;
    PermissionFilterModel *filterModelLeft;
    PermissionFilterModel *filterModelRight;
    QPushButton *copyButton;
    QPushButton *nonSecretButton;
    QPushButton *secretButton;
    QPushButton *topSecretButton;
    QComboBox *currentUserComboBox;
    ControlState state;
    QWidget buttonsWidget;
    QSignalMapper mapper;

public slots:
    void copyButtonClickedSlot();

private slots:
    void leftUpSlot();
    void rightUpSlot();
    void leftTreeViewClickedSlot(QModelIndex index);
    void rightTreeViewClickedSlot(QModelIndex index);
    void leftTreeViewActivatedSlot(QModelIndex index);
    void rightTreeViewActivatedSlot(QModelIndex index);
    void userChosenSlot(int index);
    void changeAdminControls();
    void updateButtons();
    void clearLayout(QLayout* layout, bool deleteWidgets = true);
    void changePathRight(QString right);


};

#endif // FILE_SYSTEM_VIEW_WIDGET_H
