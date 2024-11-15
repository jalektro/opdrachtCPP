#include <QCoreApplication>
#include "QDebug"
#include "websocketserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Start de server op poort 1234
    WebSocketServer server(1234);

    return a.exec();
}

#include "main.moc"
