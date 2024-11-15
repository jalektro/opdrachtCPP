#include "websocketserver.h"


WebSocketServer::WebSocketServer(quint16 port, QObject *parent)
    : QObject(parent),
    m_server(new QWebSocketServer(QStringLiteral("Weapon System Server"),
                                  QWebSocketServer::NonSecureMode, this))
{
    if (m_server->listen(QHostAddress::Any, port)) {
        qDebug() << "WebSocket server listening on port:" << port;
        //connect signal for new connections
        connect(m_server, &QWebSocketServer::newConnection, this, &WebSocketServer::onNewConnection);
    }
    else {
        qDebug() << "Failed to start websocket server on port: << port";
    }
}

WebSocketServer::~WebSocketServer() {
    //clean up connected clients and stop the server
    m_server->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void WebSocketServer::onNewConnection() {
    QWebSocket *clientSocket = m_server->nextPendingConnection();

    qDebug() << "New client connected";
    //  Connect signals to handle messages and disconnections for this client
    connect(clientSocket, &QWebSocket::textMessageReceived, this, &WebSocketServer::processMessage);
    connect(clientSocket, &QWebSocket::disconnected, this, &WebSocketServer::socketDisconnected);

    m_clients << clientSocket;    
}

// Slot: verwerkt ontvangen berichten van clients
void WebSocketServer::processMessage(const QString &message) {
    qDebug() << "Message received:" << message;

   //parse the message as JSON
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if (!doc.isObject()) {
        qDebug() << "Invalid message format";
        return;
    }

    QJsonObject obj = doc.object();
    QString weaponID = obj["weapon_id"].toString();
    QString partNumber = obj["part_number"].toString();

    //plaseholder for PDF searching logic
    QString NSN = searchForNSNInPDF(weaponID, partNumber);

    //create a JSON response with the NSN
    QJsonObject response;
    response["NSN"]= NSN;
    QJsonDocument responseDoc(response);

    //send response back to client
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    if(client){
        client->sendTextMessage(responseDoc.toJson(QJsonDocument::Compact));
    }
}

QString WebSocketServer::searchForNSNInPDF(const QString &weaponId, const QString &partNumber) {
    // Placeholder function to search in a PDF file
    // Replace this with actual PDF processing logic

    // For example:
    // 1. Load the PDF based on `weaponId`.
    // 2. Search for `partNumber` within the PDF.
    // 3. Return the NSN if found, or an empty string if not found.

    return "1234-5678"; // Placeholder NSN
}

// remove the disconnected client from the list and delete the object to free memory.
void WebSocketServer::socketDisconnected() {

    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    if (client) {
        m_clients.removeAll(client);
        client->deleteLater();
        qDebug() << "Client connection disconnect:" << client->peerAddress().toString();
    }
}
