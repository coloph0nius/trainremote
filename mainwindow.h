#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QUdpSocket;
QT_END_NAMESPACE


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QUdpSocket *udpSocket;

private slots:
    void display1(int i);
    void increase1();
    void decrease1();
    void halt1();
    void sendDatagram(int i);

};

#endif // MAINWINDOW_H
