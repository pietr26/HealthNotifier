#include "wstart.h"
#include "ui_wstart.h"

wStart::wStart(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::wStart)
{
    ui->setupUi(this);
    sound.setSource(QUrl::fromLocalFile(":/data/sound-info.wav"));
}

wStart::~wStart()
{
    delete ui;
}

void wStart::on_btnStart_clicked()
{
    showMinimized();
    ui->btnStart->setEnabled(false);
    ui->statusbar->showMessage("Work, work, work...");

    QTimer::singleShot(QRandomGenerator::global()->bounded(ui->sbxMin->value() * 1000 * 60, ui->sbxMax->value() * 1000 * 60),
        this, [=]()
           {
               showMinimized();
               sound.play();
               showNormal();
               setFocus();
               ui->btnStart->setEnabled(true);
               ui->statusbar->clearMessage();
           });
}
