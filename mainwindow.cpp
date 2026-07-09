#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial.setPortName("/dev/ttyACM0");
    serial.setBaudRate(QSerialPort::Baud9600);

    if (serial.open(QIODevice::ReadWrite)) {
        connect(&serial, &QSerialPort::readyRead, this, &MainWindow::readSerial);
        ui->StatusLabel->setText("Serial port opened successfully");
    } else {
        ui->StatusLabel->setText("Failed to open serial port");
    }

    connect(&serial, &QSerialPort::readyRead, this, &MainWindow::readSerial);
    connect(ui->On_Button, &QPushButton::clicked, this, &MainWindow::sendOn);
    connect(ui->Off_Button, &QPushButton::clicked, this, &MainWindow::sendOff);
}

void MainWindow::sendOn()
{
    if (serial.isOpen()) {
        serial.write("On\n");
    }
    printf("On button clicked\n");
}

void MainWindow::sendOff()
{
    if (serial.isOpen()) {
        serial.write("Off\n");
    }
    printf("Off button clicked\n");
}

void MainWindow::readSerial()
{
    QByteArray data = serial.readAll();
    ui->SerialOutput->moveCursor(QTextCursor::End);
    ui->SerialOutput->insertPlainText(QString::fromUtf8(data));
}

MainWindow::~MainWindow()
{
    delete ui;
}
