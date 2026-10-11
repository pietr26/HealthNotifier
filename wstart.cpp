#include "wstart.h"
#include "ui_wstart.h"

wStart::wStart(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::wStart)
{
    ui->setupUi(this);
    sound.setSource(QUrl("qrc:/data/sound-info.wav"));
    ui->lblPicture->setVisible(false);
    ui->lblInfo->setVisible(false);
}

wStart::~wStart()
{
    delete ui;
}

void wStart::on_btnStart_clicked()
{
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
               showMinimized();
               sound.play();
               showNormal();
               setFocus();
               ui->btnStart->setEnabled(true);
               ui->lblPicture->setVisible(true);
               ui->lblInfo->setVisible(true);
               ui->statusbar->clearMessage();
           });
}
