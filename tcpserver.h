#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QString>


class QTcpSocket;

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0);
    void StartServer();

signals:
    void writeComplete();
    void receivedMessage(const QString&);

public slots:
    void onNewConnection();
    void onSendMessage(const QString&);
    void readyRead();

private:
    QTcpSocket* socket_;
    QString msg_;

protected:
//    void incomingConnection(int socketDescriptor);
};

#endif // TCPSERVER_H
