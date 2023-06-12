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
    /*!
     * \brief Creates a widget and lists available serial ports
     * \param[in,out] parent
     * \param[in,out] serial_port - pointer to QSerialPort object that stores information about connection (is a member of MainWindow).
     */
    explicit PortSelection(QWidget *parent = nullptr, QSerialPort *serial_port = nullptr);
    ~PortSelection();

private slots:
    /*!
     * \brief If possible connects with choosen serial port
     */
    void on_buttonBox_accepted();

private:
    Ui::PortSelection *ui;
    QSerialPort* arduino;
};

#endif // PORTSELECTION_H
