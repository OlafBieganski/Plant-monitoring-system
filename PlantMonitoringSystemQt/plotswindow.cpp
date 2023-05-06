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
/*!
 * \brief Currently the function does not work properly and cause udefined behaviour
 * The reason behind this may be that the pointer QSerialPort* serial is passed between classes
 */
void PlotsWindow::on_actionWybierz_port_szeregowy_triggered()
{
    com_window = new PortSelection(this, arduino);
    com_window->setModal(true);
    com_window->show();
}

/*!
 * \brief Emits signal with information to switch windows and hide PlotsWindow window
 */
void PlotsWindow::on_actionOkno_g_wne_triggered()
{
    emit switch_window();
    hide();
}

