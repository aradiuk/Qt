#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject* parent = nullptr);

    int count();
    void close();

signals:
    void changed();

public slots:
    void disconnected();
    void readyRead();

protected:
    void incomingConnection(qintptr handle) override;
private:
    QList<QTcpSocket*> clients;
public:
    QString welcomeMessage;
};

#endif // SERVER_H
