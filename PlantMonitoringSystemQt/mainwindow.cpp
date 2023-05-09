#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <QDebug>
#include <QtSerialPort>
#include <QFileDialog>

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
    serial->close();
    delete serial;
    qDebug() << "Destructed";
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
    int trash, crc8;
    QTextStream arduinoData(serial);
    arduinoData >> trash >> temperature >> humidity >> ground >> sunlight >> crc8;
    /*qDebug() << "Dane: " <<  trash;
    qDebug() << temperature;
    qDebug() << humidity;
    qDebug() << ground;
    qDebug() << sunlight;
    qDebug() << crc8;*/
}

void MainWindow::on_actionWybierz_port_szeregowy_triggered()
{
    com_window = new PortSelection(this, serial);
    com_window->setModal(true);
    com_window->show();
}


void MainWindow::on_actionWykresy_triggered()
{
    if(second_window == nullptr){
        second_window = new PlotsWindow(this, serial);
        connect(second_window, &PlotsWindow::switch_window, this, &MainWindow::onSecondWindowClosed);
    }
    second_window->show();
    hide();
}

void MainWindow::onSecondWindowClosed(){
    show();
}

void MainWindow::on_actionNowa_seria_triggered()
{
    QString new_filename = QFileDialog::getSaveFileName(this, tr("Stwórz nową serię pomiarową"), QDir::currentPath(),
        tr("Pliki serii pomiarowej (*.srs);;All Files (*)"));

    if (!new_filename.isEmpty()) {
        curr_filename = new_filename;
        if(curr_file_handle != nullptr){
            curr_file_handle->close();
            delete curr_file_handle;
        }
        curr_file_handle = new QFile(curr_filename);
        //QString new_name = curr_file_handle->fileName() + ".srs";
        //curr_file_handle->rename(new_name);
        if (curr_file_handle->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)) {
            QTextStream out(curr_file_handle);
            out << "#2808\n"; //magic number of all files
        }
    }

}


void MainWindow::on_actionWybierz_serie_triggered()
{
    QString new_filename = QFileDialog::getOpenFileName(this, tr("Wybierz plik serii pomiarowej"), QDir::currentPath(),
        tr("Pliki serii pomiarowej (*.srs);;All Files (*)"));
    curr_filename = new_filename;
    qDebug() << new_filename;
    if(curr_file_handle != nullptr){
        curr_file_handle->close();
        delete curr_file_handle;
    }
    curr_file_handle = new QFile(curr_filename);
    if(!curr_file_handle->open(QIODevice::ReadWrite | QIODevice::Text)){
        QMessageBox::critical(this, "Wybierz plik serii pomiarowej", "Nie udało sie otworzyć pliku");
        delete curr_file_handle;
        return;
    }
    QTextStream file_stream(curr_file_handle);
    QString magic_nr;
    file_stream >> magic_nr;
    qDebug() << magic_nr;
    if(magic_nr != "#2808"){
        QMessageBox::critical(this, "Wybierz plik serii pomiarowej", "Niepoprawny plik.");
        curr_file_handle->close();
        delete curr_file_handle;
    }
}


void MainWindow::on_actionZapisz_pomiar_triggered()
{
    if(curr_file_handle == nullptr && curr_filename == ""){
        QMessageBox::information(this, tr("Błąd zapisu do pliku"), tr("Nie wybrano żadnego pliku serii pomiarowej"));
        return;
    }
    if(curr_file_handle == nullptr){
        QMessageBox::information(this, tr("Błąd zapisu do pliku"), tr("Wybrano niepoprawny plik: %1").arg(curr_filename));
        return;
    }
    QTextStream file_stream(curr_file_handle);
    file_stream << temperature << " " << humidity << " " << ground << " " << sunlight << "\n";
}

