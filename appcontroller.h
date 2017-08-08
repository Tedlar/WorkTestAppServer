#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include <QString>
#include <Windows.h>


class TcpServer;

class AppController : public QObject
{
    Q_OBJECT
public:
    explicit AppController(QObject *parent = nullptr);

signals:
    void setAppPathAccepted(bool);
    void sendMessage(const QString&);
    void gameWon();

public slots:
    void onSetAppPath(const QString&);
    void onSendCloseApp();
    void onWriteComplete();
    void onReceivedMessage(const QString&);

private:
    bool close_;
    QString path_;
    STARTUPINFO sInfo_;
    PROCESS_INFORMATION pInfo_;
    TcpServer* server_;

private:
    void startAppClient();
    void stopAppClient();
};

#endif // APPCONTROLLER_H
