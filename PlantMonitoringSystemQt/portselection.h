#ifndef PORTSELECTION_H
#define PORTSELECTION_H

#include <QDialog>
#include <QSerialPort>
#include <QDebug>

namespace Ui {
class PortSelection;
}

class PortSelection : public QDialog
{
    Q_OBJECT

public:
    explicit PortSelection(QWidget *parent = nullptr, QSerialPort *serial_port = nullptr);
    ~PortSelection();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::PortSelection *ui;
    QSerialPort* arduino;
};

#endif // PORTSELECTION_H
