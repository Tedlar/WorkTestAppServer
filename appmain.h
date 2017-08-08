#ifndef APPMAIN_H
#define APPMAIN_H

#include <QObject>


class AppController;
class AppView;

class AppMain : public QObject
{
    Q_OBJECT

public:
    explicit AppMain(QObject *parent = nullptr);
    ~AppMain();

private:
    AppController* appController_;
    AppView* appView_;

private:
    void createObjects();
    void createConnections();
};

#endif // APPMAIN_H
