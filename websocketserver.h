#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

class WebSocketServer : public QObject
{
    Q_OBJECT
public:
   explicit WebSocketServer(quint16 port, QObject *parent = nullptr);
   ~WebSocketServer();
   private slots:
    void onNewConnection();
    void processMessage(const QString &message);  
    void socketDisconnected();
   private:
    QWebSocketServer *m_server;
    QList<QWebSocket *> m_clients;
    QString searchForNSNInPDF(const QString &weaponId, const QString &partNumber) ;
};

#endif // WEBSOCKETSERVER_H
