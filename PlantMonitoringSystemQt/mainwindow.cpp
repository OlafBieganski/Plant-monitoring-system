#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <QDebug>
#include <QtSerialPort>
#include <QtSerialPortInfo>

void readData(QSerialPort & serial) {
    QByteArray data = serial.readAll();
    if (data.size() >= 3 && data[0] == 'H' && data[2] == 'T') {
        // Odczytaj dane z ramki
        int value = data[1];
        // Przetwórz dane i wyświetl w aplikacji
        qDebug() << "Received data:" << value;
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap plantPicture("/mnt/c/Users/olafb/OneDrive/Obrazy/roslina_zdrowa.png");
    ui->label_plant_pic->setPixmap(plantPicture);
    ui->label_plant_pic->setAlignment(Qt::AlignCenter);
    ui->label_plant_state->setAlignment(Qt::AlignCenter);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_measure_clicked()
{
    qDebug() << "clicked";
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    qDebug() << ports.size();
    foreach (const QSerialPortInfo &port, ports) {
        qDebug() << port.portName();
    }

    QSerialPort serial;
    serial.setPortName("COM3");
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    // Open the serial port
    if (!serial.open(QIODevice::ReadWrite)) {
        QSerialPort::SerialPortError error_code = serial.error();
        qDebug() << "Failed to open serial port";
        qDebug() << "Error code: " << error_code;
        return;
    }

    // Read data from the serial port
    QObject::connect(&serial, &QSerialPort::readyRead, [&]() {
        QByteArray data = serial.readAll();
        qDebug() << "Received data:" << data;
    });

    // Send data to the serial port
    QByteArray sendData = "Hello Arduino!";
    serial.write(sendData);
}
