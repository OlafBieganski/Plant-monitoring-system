#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QtSerialPort>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    plantPicture = QPixmap(":/images/roslina zdrowa.jpg");
    ui->label_plant_pic->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->label_plant_pic->setPixmap(plantPicture.scaled(ui->label_plant_pic->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->label_plant_pic->setAlignment(Qt::AlignCenter);
    ui->label_plant_state->setAlignment(Qt::AlignCenter);
    file_info = new QLabel(this);
    file_info->setFont(QFont("Arial", 9));
    ui->statusbar->setFont(QFont("Arial", 9));
    ui->statusbar->addWidget(file_info);
    file_info->setText(tr("Aktywny plik: "));
    serial = new QSerialPort(this);
    connect(this, &MainWindow::new_temp, ui->thermo_widget, &RectangleW::changeHeight);
    connect(this, &MainWindow::new_sun, ui->sun_widget, &SunW::setSunlightLevel);
    ui->frame_temp->setFrameShadow(QFrame::Raised);
    ui->frame_hum->setFrameShadow(QFrame::Sunken);
    setWindowTitle("System monitorowania roślin");
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    // Update the pixmap size based on the new size of the QLabel
    ui->label_plant_pic->setPixmap(plantPicture.scaled(ui->label_plant_pic->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

MainWindow::~MainWindow()
{
    delete ui;
    serial->close();
    delete serial;
}

void MainWindow::on_pushButton_measure_clicked()
{
    if(!serial->isOpen()){
        QMessageBox::information(this, tr("Port szeregowy"), tr("Nie podłączono do żadnego portu szeregowego"));
        return;
    }
    // wait until enough data is available
    while(serial->bytesAvailable() < 60){
        if(serial->waitForReadyRead(5000) == false){
            QMessageBox::information(this, serial->portName(), tr("Przekroczono czas transmisji: dane nie zostały odebrane."));
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
    ground = ((1020 - ground)*100) / 1020;
    sunlight = (sunlight * 100) / 7000;
    if(sunlight > 100) sunlight = 100;
    measureDateTime = QDateTime::currentDateTime();
    ui->statusbar->showMessage(tr("Pobrano pomiar."), 5000);
    emit new_temp(temperature);
    emit new_sun(sunlight);
    ui->lcdGround->display(ground);
    ui->lcd_humidity->display(humidity);
    if(ground < 10){
        plantPicture = QPixmap(":/images/roslina4.jpg");
        ui->label_plant_pic->setPixmap(plantPicture.scaled(ui->label_plant_pic->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    else if(ground < 25){
        plantPicture = QPixmap(":/images/roslina3.jpg");
        ui->label_plant_pic->setPixmap(plantPicture.scaled(ui->label_plant_pic->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    else if(ground < 70){
        plantPicture = QPixmap(":/images/roslina zdrowa.jpg");
        ui->label_plant_pic->setPixmap(plantPicture.scaled(ui->label_plant_pic->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    else{
        plantPicture = QPixmap(":/images/roslina2.jpg");
        ui->label_plant_pic->setPixmap(plantPicture.scaled(ui->label_plant_pic->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void MainWindow::on_actionWybierz_port_szeregowy_triggered()
{
    com_window = new PortSelection(this, serial);
    com_window->setModal(true);
    com_window->show();
}


void MainWindow::on_actionWykresy_triggered()
{
    static int curr_id = 0;
    plot_windows.insert(curr_id, new PlotsWindow(this, curr_filename, curr_id));
    connect(plot_windows[curr_id], &PlotsWindow::window_closed, this, &MainWindow::when_PlotsWindow_closed);
    plot_windows[curr_id]->show();
    curr_id++;
}

void MainWindow::when_PlotsWindow_closed(int _idx){
    PlotsWindow* temp = plot_windows[_idx];
    QMap<int, PlotsWindow*>::Iterator it = plot_windows.find(_idx);
    if(it != plot_windows.end()){
        plot_windows.erase(it);
    }
    delete temp;
}

void MainWindow::on_actionNowa_seria_triggered()
{
    QString new_filename = QFileDialog::getSaveFileName(this, tr("Stwórz nową serię pomiarową"), QDir::currentPath(),
        tr("Pliki serii pomiarowej - dni (*.srd);;Pliki serii pomiarowej - godziny (*.srh);;Wszystkie pliki (*)"));

    if (!new_filename.isEmpty()) {
        curr_filename = new_filename;
        QFile file_handler(curr_filename);
        //QString new_name = curr_file_handle->fileName() + ".srs";
        //curr_file_handle->rename(new_name);
        if (file_handler.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file_handler);
            out << "#2808"; //magic number of all files
            file_handler.close();
            file_info->setText(tr("Aktywny plik: %1").arg(getFilename(curr_filename)));
        }
    }

}


void MainWindow::on_actionWybierz_serie_triggered()
{
    QString new_filename = QFileDialog::getOpenFileName(this, tr("Wybierz plik serii pomiarowej"), QDir::currentPath(),
        tr("Pliki serii pomiarowej - dni (*.srd);;Pliki serii pomiarowej - godziny (*.srh);;Wszystkie pliki (*)"));
    if(new_filename.isEmpty()) return;
    curr_filename = new_filename;
    QFile file_handler(curr_filename);
    if(!file_handler.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::critical(this, tr("Wybierz plik serii pomiarowej"), tr("Nie udało sie otworzyć pliku"));
        return;
    }
    QTextStream file_stream(&file_handler);
    QString magic_nr;
    file_stream >> magic_nr;
    if(magic_nr != "#2808"){
        QMessageBox::critical(this, tr("Wybierz plik serii pomiarowej"), tr("Niepoprawny plik."));
        curr_filename = "";
    }
    file_info->setText(tr("Aktywny plik: %1").arg(getFilename(curr_filename)));
    file_handler.close();
}


void MainWindow::on_actionZapisz_pomiar_triggered()
{
    if(curr_filename.isEmpty()){
        QMessageBox::information(this, tr("Błąd zapisu do pliku"), tr("Nie wybrano żadnego pliku serii pomiarowej"));
        return;
    }
    QFile file_handler(curr_filename);
    if(!file_handler.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)){
        QMessageBox::information(this, tr("Błąd zapisu do pliku"), tr("Wybrano niepoprawny plik: %1").arg(curr_filename));
        return;
    }
    QTextStream file_stream(&file_handler);
    file_stream << "\n" << temperature << " " << humidity << " " << ground << " " << sunlight << " ";
    if(getFilename(curr_filename).back() == 'd') file_stream << measureDateTime.date().toString("dd-MM-yyyy");
    if(getFilename(curr_filename).back() == 'h') file_stream << measureDateTime.time().toString();
    ui->statusbar->showMessage(tr("Zapisano do pliku: %1").arg(getFilename(curr_filename)), 5000);
    file_handler.close();
}

QString MainWindow::getFilename(const QString& path){
    QFileInfo fileInfo(path);
    return fileInfo.fileName();
}

void MainWindow::on_actionJ_zyk_Language_triggered()
{
    QStringList items;
    items << tr("Polski") << tr("Angielski");

    bool ok;
    QString item = QInputDialog::getItem(this, tr("QInputDialog::getItem()"),
                                         tr("Season:"), items, 0, false, &ok);
    if (ok && !item.isEmpty()){

    }
}

