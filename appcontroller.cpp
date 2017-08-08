#include "appcontroller.h"
#include "tcpserver.h"

#include <QFileInfo>
#include <QDebug>
#include <QApplication>

#include <Windows.h>


AppController::AppController(QObject *parent) : QObject(parent), close_(false) {
    server_ = new TcpServer(parent);
    connect(this, SIGNAL(sendMessage(QString)), server_, SLOT(onSendMessage(QString)));
    connect(server_, SIGNAL(writeComplete()), this, SLOT(onWriteComplete()));
    connect(server_, SIGNAL(receivedMessage(QString)), this, SLOT(onReceivedMessage(QString)));
}

void AppController::onSetAppPath(const QString& _path) {
    path_ = _path + "\\AppClient.exe";
    QFileInfo check_file(path_);
    if (check_file.exists() && check_file.isExecutable()) {
        emit setAppPathAccepted(true);
        startAppClient();
    } else {
        emit setAppPathAccepted(false);
    }
}

void AppController::onSendCloseApp() {
    close_ = true;
    emit sendMessage("zamknij");
}

void AppController::onWriteComplete() {
    if (close_)
        stopAppClient();
}

void AppController::onReceivedMessage(const QString& _text) {
    if (_text == "wygrana")
        emit gameWon();
}

void AppController::startAppClient() {
    LPCWSTR path = (const wchar_t*) path_.utf16();

    ZeroMemory( &sInfo_, sizeof(sInfo_) );
    sInfo_.cb = sizeof(sInfo_);
    ZeroMemory( &pInfo_, sizeof(pInfo_) );

    // Start the child process.
    if(!CreateProcess(path, NULL, NULL, NULL, FALSE,
                       0, NULL, NULL, &sInfo_, &pInfo_)){
        qDebug() << "CreateProcess failed [" << GetLastError() << "]";
        return;
    }

    // Start TcpServer
    server_->StartServer();
}

void AppController::stopAppClient() {
    WaitForSingleObject(pInfo_.hProcess, INFINITE);
    CloseHandle(pInfo_.hProcess);
    qApp->exit();
}
