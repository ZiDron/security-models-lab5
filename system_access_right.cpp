#include "system_access_right.h"
#include <QStringList>

SystemAccessRight::SystemAccessRight(Database *database) {
    this->database = database;
}

//void SystemAccessRight::changeRight(QString path, SystemAccessRight::AccessRight right) {
////    int index = findIndexPath(path);
////    if (index == -1) {
////        rightList.append(QPair<QString, AccessRight>(path, right));
////    } else {
////        rightList[index].second = right;
//    //    }
//}

//void SystemAccessRight::changeRight(QString path, QString rightName) {
//    database->changeRight(path, rightName);
//}

//SystemAccessRight::AccessRight SystemAccessRight::getAccessRight(QString path) {
//    int index = findIndexPath(path);
//    if (index == -1) {
//        return AccessRight::NonSecret;
//    } else {
//        return rightList.at(index).second;
//    }
//}

//int SystemAccessRight::findIndexPath(QString path) {
//    for (int i = 0; i < rightList.size(); i++) {
//        if (rightList.at(i).first == path) {
//            return i;
//        }
//    }
//    return -1;
//}

bool SystemAccessRight::trueCopy(QString srcPath, QString dstPath) {
    QDir srcDir(srcPath);
    QDir dstDir(dstPath);
    QStringList files = srcDir.entryList();
    for (int i = 0; i < files.size(); i++) {
        QFileInfo info(srcDir.absolutePath() + "/" + files.at(i));
        if (info.isDir() && info.fileName() != ".." && info.fileName() != ".") {
            srcDir.mkpath(dstDir.absolutePath() + "/" + files.at(i));
            trueCopy(srcDir.absolutePath() + "/" + files.at(i), dstDir.absolutePath() + "/" + srcDir.dirName() + "/" + files.at(i));
        } else if (info.isFile()) {
            srcDir.mkpath(dstDir.absolutePath());
            QFile::copy(srcDir.absolutePath() + "/" + files.at(i), dstDir.absolutePath() + "/" + files.at(i));
        }
    }
}

bool SystemAccessRight::copy(QString srcPath, QString dstPath) {
    QDir srcDir(srcPath);
    QDir dstDir(dstPath + "/" + srcDir.dirName());
    QStringList files = srcDir.entryList();
    for (int i = 0; i < files.size(); i++) {
        QFileInfo info(srcDir.absolutePath() + "/" + files.at(i));
        QString topFolderName = srcDir.absolutePath().remove("/" + srcDir.dirName());
        if (database->getAccessRight(topFolderName)->getLevel() > database->getAccessRight(dstPath)->getLevel()) {
            emit wrongAccessRights(srcPath, dstPath);
            return false;
        }
        if (info.isDir() && info.fileName() != ".." && info.fileName() != ".") {
            srcDir.mkpath(dstDir.absolutePath() + "/" + files.at(i));
            trueCopy(srcDir.absolutePath() + "/" + files.at(i), dstDir.absolutePath() + "/" + files.at(i));
        } else if (info.isFile()) {
            srcDir.mkpath(dstDir.absolutePath());
            QFile::copy(srcDir.absolutePath() + "/" + files.at(i), dstDir.absolutePath() + "/" + files.at(i));
        }
    }
    if (files.size() == 0) {
        QDir temp = srcDir;
        temp.cdUp();
        if (database->getAccessRight(temp.absolutePath())->getLevel() > database->getAccessRight(dstPath)->getLevel()) {
            emit wrongAccessRights(srcPath, temp.absolutePath());
            return false;
        }
        srcDir.mkpath(dstPath);
        return QFile::copy(srcDir.absolutePath(), dstDir.absolutePath());
    }
}
