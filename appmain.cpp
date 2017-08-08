#include "appmain.h"
#include "appcontroller.h"
#include "appview.h"
#include "tcpserver.h"


AppMain::AppMain(QObject *parent) : QObject(parent) {
    createObjects();
    createConnections();
    appView_->show();
}

AppMain::~AppMain() {
    delete appView_;
}

void AppMain::createObjects() {
    appView_ = new AppView();
    appController_ = new AppController(appView_);
}

void AppMain::createConnections() {
    connect(appView_, SIGNAL(setAppPath(QString)), appController_, SLOT(onSetAppPath(QString)));
    connect(appView_, SIGNAL(sendMessage(QString)), appController_, SIGNAL(sendMessage(QString)));
    connect(appView_, SIGNAL(sendCloseApp()), appController_, SLOT(onSendCloseApp()));
    connect(appController_, SIGNAL(setAppPathAccepted(bool)), appView_, SLOT(onSetAppPathAccepted(bool)));
    connect(appController_, SIGNAL(gameWon()), appView_, SLOT(onGameWon()));
}
