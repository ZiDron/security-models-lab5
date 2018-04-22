#include "application.h"


Application::Application() : QObject(),
    systemAccessRight(&database),
    widget(&systemAccessRight, &database)
{

}

void Application::show() {
    widget.show();
}

//void Application::changeAccessRight(QDir *folder, SystemAccessRight::AccessRight right) {
//    systemAccessRight.changeRight(folder->absolutePath(), right);
//}

//void Application::changeAccessRight(QString path, SystemAccessRight::AccessRight right) {
//    systemAccessRight.changeRight(path, right);
//}

//SystemAccessRight::AccessRight Application::getAccessRight(QString path) {
//    return systemAccessRight.getAccessRight(path);
//}

