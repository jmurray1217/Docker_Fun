#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;

    QSerialPort serial;
    int hexValue = 0;

private slots:
    void readSerial();
    void sendOn();
    void sendOff();
    void getHexValue();
    void getServoPosition(int value);
};
#endif // MAINWINDOW_H
