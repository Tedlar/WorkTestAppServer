#include "appview.h"
#include "ui_appview.h"
#include <QMessageBox>


AppView::AppView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AppView)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    connect(ui->p1_bt, SIGNAL(clicked()), this, SLOT(onClickedSendPath()));
    connect(ui->p2_bt_1, SIGNAL(clicked()), this, SLOT(onClickedSendMessage()));
    connect(ui->p2_bt_2, SIGNAL(clicked()), this, SLOT(onClickedSendCommand()));
    connect(ui->p2_bt_3, SIGNAL(clicked()), this, SLOT(onClickedSendCloseApp()));
}

AppView::~AppView() {
    delete ui;
}

void AppView::onClickedSendPath() {
    emit setAppPath(ui->p1_le->text());
}

void AppView::onClickedSendMessage() {
    emit sendMessage(ui->p2_le->text());
}

void AppView::onClickedSendCommand() {
    if (!validateNumbers()) return;
    cmd_ = "losuj ";
    cmd_ += QString::number(ui->p2_sb_1->value()) + " ";
    cmd_ += QString::number(ui->p2_sb_2->value()) + " ";
    cmd_ += QString::number(ui->p2_sb_3->value());
    emit sendMessage(cmd_);
}

void AppView::onClickedSendCloseApp() {
    emit sendCloseApp();
}

void AppView::onSetAppPathAccepted(bool _accepted) {
    if (_accepted) {
        ui->stackedWidget->setCurrentIndex(1);
    } else {
        ui->p1_le->setText("Wrong AppClient Path");
    }
}

void AppView::onGameWon() {
    QMessageBox::information(this, tr("Message"), tr("Gra Wygrana!"));
}

bool AppView::validateNumbers() {
    if (ui->p2_sb_1->value() == 0 ||
            ui->p2_sb_2->value() == 0 ||
            ui->p2_sb_3->value() == 0)
        return false;
    if (ui->p2_sb_1->value() == ui->p2_sb_2->value() ||
            ui->p2_sb_1->value() == ui->p2_sb_3->value() ||
            ui->p2_sb_2->value() == ui->p2_sb_3->value())
        return false;
    return true;
}
