#include "plotswidget.h"
#include "ui_plotswidget.h"

PlotsWidget::PlotsWidget(QWidget *parent, QString file_name, int _idx) :
    QWidget(parent),
    ui(new Ui::PlotsWidget),
    curr_file_name(file_name),
    idx(_idx)
{
    ui->setupUi(this);

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
        for(QCustomPlot* graph : plots){

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

PlotsWidget::~PlotsWidget()
{
    delete ui;
    emit window_closed(idx);
}
