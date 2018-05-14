#include "application.h"


Application::Application() : QObject(),
    systemAccessRight(&database),
    widget(&systemAccessRight, &database) {

}
