#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ServoPositionController->setRange(0, 1023);
    serial.setPortName("/dev/ttyACM0");
    serial.setBaudRate(QSerialPort::Baud9600);

    if (serial.open(QIODevice::ReadWrite)) {
        connect(&serial, &QSerialPort::readyRead, this, &MainWindow::readSerial);
        ui->StatusLabel->setText("Serial port opened successfully");
    } else {
        ui->StatusLabel->setText("Failed to open serial port");
    }

    connect(&serial, &QSerialPort::readyRead, this, &MainWindow::readSerial);
    // connect(ui->ServoPositionController, &QSlider::sliderReleased, this, &MainWindow::getServoPosition);
    connect(ui->ServoPositionController, &QSlider::valueChanged, this,
        [this](int value){
            getServoPosition(value);
            qDebug() << value;
        });
    connect(ui->checkBox_1, &QCheckBox::clicked, this,  &MainWindow::getHexValue);
    connect(ui->checkBox_2, &QCheckBox::clicked, this,  &MainWindow::getHexValue);
    connect(ui->checkBox_3, &QCheckBox::clicked, this,  &MainWindow::getHexValue);
    connect(ui->checkBox_4, &QCheckBox::clicked, this,  &MainWindow::getHexValue);
    connect(ui->On_Button, &QPushButton::clicked, this, &MainWindow::sendOn);
    connect(ui->Off_Button, &QPushButton::clicked, this, &MainWindow::sendOff);
}

void MainWindow::sendOn()
{
    if (serial.isOpen()) {
        serial.write("0xF\n");
    }
    ui->checkBox_1->setChecked(true);
    ui->checkBox_2->setChecked(true);
    ui->checkBox_3->setChecked(true);
    ui->checkBox_4->setChecked(true);
}

void MainWindow::sendOff()
{
    if (serial.isOpen()) {
        serial.write("0x0\n");
    }
    ui->checkBox_1->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->checkBox_4->setChecked(false);
}

void MainWindow::getHexValue()
{
    if (serial.isOpen()) {
        int value = 0;
        if (ui->checkBox_1->isChecked()) value |= 0x1;
        if (ui->checkBox_2->isChecked()) value |= 0x2;
        if (ui->checkBox_3->isChecked()) value |= 0x4;
        if (ui->checkBox_4->isChecked()) value |= 0x8;

        QString command = QString::number(ui->ServoPositionController->value()) + " ";
        command += QString("0x%1\n").arg(value, 1, 16);
        printf("Command: %s\n", command.toUtf8().constData());
        serial.write(command.toUtf8());
        hexValue = value;
    }
}
 void MainWindow::getServoPosition(int value){
    // QString command = QString::number(ui->ServoPositionController->value()) + " ";
    QString command = QString::number(value) + " ";
    command += QString("0x%1\n").arg(hexValue, 1, 16);
    printf("Command: %s\n", command.toUtf8().constData());
    serial.write(command.toUtf8());
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
