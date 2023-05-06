#include "plotswindow.h"
#include "ui_plotswindow.h"

PlotsWindow::PlotsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlotsWindow)
{
    ui->setupUi(this);
}

PlotsWindow::~PlotsWindow()
{
    delete ui;
}

void PlotsWindow::on_actionWybierz_port_szeregowy_triggered()
{
    emit change_serial_port();
}


void PlotsWindow::on_actionOkno_g_wne_triggered()
{
    emit switch_window();
    hide();
}

