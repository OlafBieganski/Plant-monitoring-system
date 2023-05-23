#include "plotswindow.h"
#include "ui_plotswindow.h"

PlotsWindow::PlotsWindow(QWidget *parent, QSerialPort* serial, QString file_name) :
    QMainWindow(parent),
    ui(new Ui::PlotsWindow)
{
    ui->setupUi(this);
    arduino = serial;
    curr_file_name = file_name;

    ui->plot_ground_humidity->addGraph();
    ui->plot_ground_humidity->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot_ground_humidity->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->plot_ground_humidity->xAxis->setLabel("Time");
    ui->plot_ground_humidity->yAxis->setLabel("%");
    /*ui->plot_ground_humidity->graph(0)->addData(1,1);
    ui->plot_ground_humidity->graph(0)->addData(2,3);
    ui->plot_ground_humidity->graph(0)->addData(3,4);*/

    ui->plot_humidity_ambient->addGraph();

    ui->plot_temperature->addGraph();

    ui->plot_sunlight->addGraph();

    //********************************
    for(int i = 0; i < 10; i++){
        ui->plot_sunlight->graph(0)->addData(i,i);
    }
}

PlotsWindow::~PlotsWindow()
{
    delete ui;
}

void PlotsWindow::on_actionWybierz_port_szeregowy_triggered()
{
    for(int i = 0; i < 10; i++){
        ui->plot_ground_humidity->graph(0)->addData(i,i);
        qDebug() << i;
    }
}

void PlotsWindow::on_actionOkno_g_wne_triggered()
{
    emit switch_window();
    hide();
}


void PlotsWindow::on_actionWybierz_serie_triggered()
{
    if(curr_file_name.isEmpty()){
        qDebug() << "Filename parameter not given or is a wrong one";
        return;
    }
    QFile file_handler(curr_file_name);
    if(file_handler.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream file_out(&file_handler);
        if(file_out.readLine() != "#2808"){
            qDebug() << "Wrong file magic number";
            file_handler.close();
            return;
        }
        QCustomPlot* plots[4] = {ui->plot_temperature, ui->plot_humidity_ambient, ui->plot_ground_humidity, ui->plot_sunlight};
        for(QCustomPlot* graph : plots){
            graph->xAxis->setRange(0,10);
            graph->yAxis->setRange(0,100);
            graph->xAxis->setLabel("Time");
        }
        uint time = 0;
        while (!file_out.atEnd()) {
            //QVector<QString> data; //temperature, humidity, ground, sunlight
            for(QCustomPlot* graph : plots){
                QString data;
                file_out >> data;
                qDebug() << data.toDouble();
                graph->graph(0)->addData(time, data.toDouble());
            }
            time++;
        }
        file_handler.close();
    }
}




















