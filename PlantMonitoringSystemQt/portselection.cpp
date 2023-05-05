#include "portselection.h"
#include "ui_portselection.h"
#include <QSerialPortInfo>
#include <QMessageBox>

PortSelection::PortSelection(QWidget *parent, QSerialPort *serial_port) :
    QDialog(parent),
    ui(new Ui::PortSelection)
{
    arduino = serial_port;
    ui->setupUi(this);
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    foreach (const QSerialPortInfo &port, ports) {
        ui->comboBox->addItem(port.portName());
    }
}

PortSelection::~PortSelection()
{
    delete ui;
}

void PortSelection::on_buttonBox_accepted()
{
    if(arduino->isOpen()){
        arduino->close();
    }
    arduino->setPortName(ui->comboBox->currentText());
    arduino->setBaudRate(QSerialPort::Baud9600);
    arduino->setDataBits(QSerialPort::Data8);
    arduino->setParity(QSerialPort::NoParity);
    arduino->setStopBits(QSerialPort::OneStop);
    arduino->setFlowControl(QSerialPort::NoFlowControl);

    // Open the serial port
    if (!arduino->open(QSerialPort::ReadOnly)) {
        QMessageBox::information(this, ui->comboBox->currentText(), "Błąd podczas łączenia z portem");
    }
    else{
        QMessageBox::information(this, ui->comboBox->currentText(), "Nawiązano połączenie z portem");
    }
}

