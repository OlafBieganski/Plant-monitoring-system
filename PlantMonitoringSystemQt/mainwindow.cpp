#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <QDebug>
#include <QtSerialPort>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap plantPicture("C:/Users/olafb/OneDrive/Obrazy/roslina_zdrowa.png");
    ui->label_plant_pic->setPixmap(plantPicture);
    ui->label_plant_pic->setAlignment(Qt::AlignCenter);
    ui->label_plant_state->setAlignment(Qt::AlignCenter);
    serial = new QSerialPort(this);
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

    serial->setPortName("COM1");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    // Open the serial port
    if (!serial->open(QSerialPort::ReadOnly)) {
        QSerialPort::SerialPortError error_code = serial->error();
        qDebug() << "Failed to open serial port";
        qDebug() << "Error code: " << error_code;
        return;
    }

    // wait until enough data is available
    while(serial->bytesAvailable() < 60){
        if(serial->waitForReadyRead() == false){
            qDebug() << "Error in void MainWindow::on_pushButton_measure_clicked(): " << serial->error();
            return;
        }
    }

    // find the beginning of the frame in incoming data
    char byte = '0';
    do{
        serial->read(&byte, 1);
    }while(byte != 'H');

    // parse the data frame
    int trash, temperature, humidity, ground, sunlight, crc8;
    QTextStream arduinoData(serial);
    arduinoData >> trash >> temperature >> humidity >> ground >> sunlight >> crc8;
    qDebug() << "Dane: " <<  trash;
    qDebug() << temperature;
    qDebug() << humidity;
    qDebug() << ground;
    qDebug() << sunlight;
    qDebug() << crc8;
    serial->close();
}
