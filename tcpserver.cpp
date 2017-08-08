#include "tcpserver.h"
#include <QTcpSocket>


TcpServer::TcpServer(QObject *parent) :
    QTcpServer(parent) {
    connect(this, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

void TcpServer::StartServer() {
    if(!this->listen(QHostAddress::Any, 1234)) {
        qDebug() << "Could not start server";
    } else {
        qDebug() << "Listening...";
    }
}

void TcpServer::onSendMessage(const QString &_text) {
    qDebug() << "Send Message";
    socket_->write(_text.toUtf8());
}

void TcpServer::onNewConnection() {
    qDebug() << "Connecting...";
    socket_ = this->nextPendingConnection();
    socket_->setParent(this);
    connect(socket_, SIGNAL(bytesWritten(qint64)), this, SIGNAL(writeComplete()));
    connect(socket_, SIGNAL(readyRead()), this, SLOT(readyRead()));
    qDebug() << "Connected";
}

void TcpServer::readyRead() {
    qDebug() << "Reading...";
    msg_ = QString::fromUtf8(socket_->readAll());
    emit receivedMessage(msg_);
}
