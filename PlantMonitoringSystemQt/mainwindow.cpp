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
    if(!serial->isOpen()){
        QMessageBox::information(this, "Port szeregowy", "Nie podłączono do żadnego portu szeregowego");
        return;
    }
    // wait until enough data is available
    while(serial->bytesAvailable() < 60){
        if(serial->waitForReadyRead(5000) == false){
            QMessageBox::information(this, serial->portName(), "Przekroczono czas transmisji: dane nie zostały odebrane.");
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
}

void MainWindow::on_actionWybierz_port_szeregowy_triggered()
{
    com_window = new PortSelection(this, serial);
    com_window->setModal(true);
    com_window->show();
}


void MainWindow::on_actionWykresy_triggered()
{

}

