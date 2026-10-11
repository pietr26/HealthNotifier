#include "wstart.h"
#include "ui_wstart.h"

#include <QApplication>
#include <QMenu>

wStart::wStart(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::wStart)
{
    ui->setupUi(this);
    player.setAudioOutput(&audioOutput);
    player.setSource(QUrl("qrc:/data/sound-info.wav"));
    ui->lblPicture->setVisible(false);
    ui->lblInfo->setVisible(false);

    QMenu *trayMenu = new QMenu(this);
    trayMenu->addAction("Quit", qApp, &QApplication::quit);
    trayIcon.setIcon(QIcon(":/data/icon.ico"));
    trayIcon.setToolTip("HealthNotifier - waiting...");
    trayIcon.setContextMenu(trayMenu);
}

wStart::~wStart()
{
    delete ui;
}

void wStart::on_btnStart_clicked()
{
    if (QSystemTrayIcon::isSystemTrayAvailable())
    {
        trayIcon.show();
        hide();
    }
    else
        showMinimized();

    ui->btnStart->setEnabled(false);
    ui->lblPicture->setVisible(false);
    ui->lblInfo->setVisible(false);
    ui->statusbar->showMessage("Coding, coding, coding...");

    const int minMs = qMin(ui->sbxMin->value(), ui->sbxMax->value()) * 1000 * 60;
    const int maxMs = qMax(ui->sbxMin->value(), ui->sbxMax->value()) * 1000 * 60;
    const int delay = minMs == maxMs ? minMs : QRandomGenerator::global()->bounded(minMs, maxMs);

    QTimer::singleShot(delay,
        this, [=]()
           {
               trayIcon.hide();
               player.play();
               showNormal();
               raise();
               activateWindow();
               ui->btnStart->setEnabled(true);
               ui->lblPicture->setVisible(true);
               ui->lblInfo->setVisible(true);
               ui->statusbar->clearMessage();
           });
}
