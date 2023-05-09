#include "plotswindow.h"
#include "ui_plotswindow.h"

PlotsWindow::PlotsWindow(QWidget *parent, QSerialPort* serial) :
    QMainWindow(parent),
    ui(new Ui::PlotsWindow)
{
    ui->setupUi(this);
    arduino = serial;
}

PlotsWindow::~PlotsWindow()
{
    delete ui;
}

void PlotsWindow::on_actionWybierz_port_szeregowy_triggered()
{
    return; // delete for a function to work
    // here is a code to debug
    com_window = new PortSelection(this, arduino);
    com_window->setModal(true);
    com_window->show();
}

void PlotsWindow::on_actionOkno_g_wne_triggered()
{
    emit switch_window();
    hide();
}

