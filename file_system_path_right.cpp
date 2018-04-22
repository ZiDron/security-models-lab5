#include "file_system_path_right.h"

FileSystemPathRight::FileSystemPathRight(QString path, AccessRight *right) {
    this->path = path;
    this->right = right;
}

QString FileSystemPathRight::getPath() {
    return path;
}

AccessRight *FileSystemPathRight::getRights() {
    return right;
}

void FileSystemPathRight::setRight(AccessRight *newAccesRight) {
    this->right = newAccesRight;
}
