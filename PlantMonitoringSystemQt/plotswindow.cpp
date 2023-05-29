#include "plotswindow.h"
#include "ui_plotswindow.h"
#include<QDateTime>

struct PlantData
{
    QVector<int> values;
    QDateTime time;
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
    ui->plot_ground_humidity->yAxis->setRange(0, 100);

    ui->plot_humidity_ambient->addGraph();
    ui->plot_humidity_ambient->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot_humidity_ambient->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->plot_humidity_ambient->xAxis->setLabel("Time");
    ui->plot_humidity_ambient->yAxis->setLabel("%");
    ui->plot_humidity_ambient->yAxis->setRange(0, 100);

    ui->plot_temperature->addGraph();
    ui->plot_temperature->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot_temperature->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->plot_temperature->xAxis->setLabel("Time");
    ui->plot_temperature->yAxis->setLabel(QChar(0x00B0) + 'C');
    ui->plot_temperature->yAxis->setRange(0, 100);

    ui->plot_sunlight->addGraph();
    ui->plot_sunlight->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot_sunlight->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->plot_sunlight->xAxis->setLabel("Time");
    ui->plot_sunlight->yAxis->setLabel("%");
    ui->plot_sunlight->yAxis->setRange(0, 100);

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

        QVector<PlantData> points;
        QFileInfo info(curr_file_name);
        QChar file_type = info.fileName().back();

        while (!file_out.atEnd()) {
            PlantData temp_p;
            for(int i = 0; i < 4; i++){
                QString data;
                file_out >> data;
                temp_p.values.push_back(data.toInt());
            }
            QString time_string;
            file_out >> time_string;
            if(file_type == 'd') temp_p.time = QDateTime::fromString(time_string, "dd-MM-yyyy");
            if(file_type == 'h'){
                temp_p.time = QDateTime::fromString(time_string, "HH:mm:ss");
                temp_p.time = temp_p.time.addYears(100);
            }
            points.push_back(temp_p);
            qDebug() << temp_p.time;
        }
        file_handler.close();

        QVector<QCPGraphData> data_set[4];
        for(const PlantData &curr : points){
            for(int i = 0; i < 4; i++){
                QCPGraphData temp;
                temp.key = curr.time.toSecsSinceEpoch();
                temp.value = curr.values[i];
                data_set[i].push_back(temp);
                qDebug() << temp.key;
            }
        }

        QCustomPlot* plots[4] = {ui->plot_temperature, ui->plot_humidity_ambient, ui->plot_ground_humidity, ui->plot_sunlight};
        for(int i = 0; i < 4; i++){
            plots[i]->graph()->data()->set(data_set[i]);
            QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
            if(file_type == 'd') dateTicker->setDateTimeFormat("dd-MM-yyyy");
            if(file_type == 'h') dateTicker->setDateTimeFormat("HH:mm:ss");
            plots[i]->xAxis->setTicker(dateTicker);
            plots[i]->xAxis->setRange(points.front().time.toTime_t(), points.back().time.toTime_t());
        }
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
