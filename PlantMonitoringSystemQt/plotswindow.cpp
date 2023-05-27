#include "plotswindow.h"
#include "ui_plotswindow.h"
#include<QDateTime>

struct PlantData
{
    QVector<int> y_points;
    QDateTime x_point;
};

PlotsWindow::PlotsWindow(QWidget *parent, QString file_name, int _idx) :
    QMainWindow(parent),
    ui(new Ui::PlotsWindow)
{
    ui->setupUi(this);
    curr_file_name = file_name;
    idx = _idx;
    QFileInfo info(file_name);
    setWindowTitle(tr("Wykresy: %1").arg(info.fileName()));

    //initial plots setup
    ui->plot_ground_humidity->addGraph();
    ui->plot_ground_humidity->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot_ground_humidity->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->plot_ground_humidity->xAxis->setLabel("Time");
    ui->plot_ground_humidity->yAxis->setLabel("%");

    ui->plot_humidity_ambient->addGraph();
    ui->plot_humidity_ambient->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot_humidity_ambient->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->plot_humidity_ambient->xAxis->setLabel("Time");
    ui->plot_humidity_ambient->yAxis->setLabel("%");

    ui->plot_temperature->addGraph();
    ui->plot_temperature->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot_temperature->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->plot_temperature->xAxis->setLabel("Time");
    ui->plot_temperature->yAxis->setLabel((QString)248 + 'C');

    ui->plot_sunlight->addGraph();
    ui->plot_sunlight->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot_sunlight->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->plot_sunlight->xAxis->setLabel("Time");
    ui->plot_sunlight->yAxis->setLabel("%");

    // draw plots with data from file
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
        QFileInfo info(curr_file_name);
        QChar file_type = info.fileName().back();
        for(QCustomPlot* graph : plots){
            //if(file_type == 'd') graph->xAxis->setRange();
        }
        uint time = 0;
        while (!file_out.atEnd()) {
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

PlotsWindow::~PlotsWindow()
{
    qDebug() << "PlotsWindow destructed. ID: " << idx;
    delete ui;
}

void PlotsWindow::closeEvent(QCloseEvent* event)
{
    emit window_closed(idx);  // Emit the custom signal when the window is closed
    QMainWindow::closeEvent(event);  // Call the base class implementation
}
