#include "server.h"

Server::Server(QObject* parent)
    : QTcpServer(parent)
    , welcomeMessage("Hello!")
    , clients()
{

}

int Server::count()
{
    return clients.size();
}

void Server::close()
{
    for (QTcpSocket* client : clients) {
        client->close();
    }
    qDeleteAll(clients);
    clients.clear();
    emit changed();
    QTcpServer::close();
}

void Server::disconnected()
{
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    if (!client) {
        return;
    }
    clients.removeAll(client);
    disconnect(client, &QTcpSocket::disconnected, this, &Server::disconnected);
    disconnect(client, &QTcpSocket::readyRead, this, &Server::readyRead);
    delete client;
    emit changed();
}

void Server::readyRead()
{
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    if (!client) {
        return;
    }
    QByteArray data = client->readAll();
    for (QTcpSocket* client : clients) {
        client->write(data);
    }
}

void Server::incomingConnection(qintptr handle)
{
    QTcpSocket* client = new QTcpSocket();
    client->setSocketDescriptor(handle);
    if (!client->waitForConnected(3000)) {
        delete client;
        return;
    }
    clients.append(client);
    connect(client, &QTcpSocket::disconnected, this, &Server::disconnected);
    connect(client, &QTcpSocket::readyRead, this, &Server::readyRead);
    emit changed();
    client->write(welcomeMessage.toLatin1());
}
