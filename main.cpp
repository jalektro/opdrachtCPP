#include <QApplication>
#include "mainwindow.h"
#include "websocketserver.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Start de server op poort 1234
    WebSocketServer server(1234);

    // make and show mainwindow
    MainWindow mainWindow;
    mainWindow.setWindowTitle("Weaponlist");
    mainWindow.resize(800,600);
    mainWindow.show();

    return a.exec();
}

#include "main.moc"
