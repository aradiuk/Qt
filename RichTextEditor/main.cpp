#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("My organisation");
    a.setOrganizationDomain("My domain");
    a.setApplicationName("My app");
    a.setApplicationDisplayName("My official name");
    a.setApplicationVersion("1.0");
    MainWindow w;
    w.show();
    return QApplication::exec();
}
