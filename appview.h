#ifndef APPVIEW_H
#define APPVIEW_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class AppView;
}

class AppView : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppView(QWidget *parent = 0);
    ~AppView();

signals:
    void setAppPath(const QString&);
    void sendMessage(const QString&);
    void sendCloseApp();

public slots:
    void onClickedSendPath();
    void onClickedSendMessage();
    void onClickedSendCommand();
    void onClickedSendCloseApp();
    void onSetAppPathAccepted(bool);
    void onGameWon();

private:
    bool validateNumbers();

private:
    Ui::AppView *ui;
    QString cmd_;
};

#endif // APPVIEW_H
