#ifndef WSTART_H
#define WSTART_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTimer>
#include <QRandomGenerator>
#include <QSystemTrayIcon>

QT_BEGIN_NAMESPACE
namespace Ui {
class wStart;
}
QT_END_NAMESPACE

class wStart : public QMainWindow
{
    Q_OBJECT

public:
    wStart(QWidget *parent = nullptr);
    ~wStart();

private slots:
    void on_btnStart_clicked();

private:
    Ui::wStart *ui;

    QAudioOutput audioOutput;
    QMediaPlayer player;
    QSystemTrayIcon trayIcon;
};
#endif // WSTART_H
