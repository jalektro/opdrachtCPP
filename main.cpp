#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // make and show mainwindow
    MainWindow mainWindow;

    mainWindow.show();
    return a.exec();
}
