#ifndef PLOTSWINDOW_H
#define PLOTSWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <portselection.h>

namespace Ui {
class PlotsWindow;
}

class PlotsWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Creates a PlotsWindow object
     * \param parent
     * \param serial - pointer to a serial port handler that our external device is connected to
     * \param file_name - name of the file with data to be visualized on the plots
     * \see PortSelection
     */
    explicit PlotsWindow(QWidget *parent = nullptr, QSerialPort* serial = nullptr, QString file_name = "");
    ~PlotsWindow();

signals:
    /*!
     * \brief signal that is emitted when a window is supposed to be changed
     */
    void switch_window();

private slots:
    /*!
    * \brief Currently the function does not work properly and cause udefined behaviour
    * The reason behind this may be that the pointer QSerialPort* serial is passed between classes
    */
    void on_actionWybierz_port_szeregowy_triggered();
    /*!
    * \brief Emits signal with information to switch windows and hide PlotsWindow window
    */
    void on_actionOkno_g_wne_triggered();
    /*!
     * \brief Open file with a measurement data and displays it on plots
     */
    void on_actionWybierz_serie_triggered();

private:
    Ui::PlotsWindow *ui;
    QSerialPort* arduino;
    PortSelection* com_window;
    QString curr_file_name;
};

#endif // PLOTSWINDOW_H
