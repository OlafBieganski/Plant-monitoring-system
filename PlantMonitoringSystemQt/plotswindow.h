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
    explicit PlotsWindow(QWidget *parent = nullptr, QSerialPort* serial = nullptr);
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

private:
    Ui::PlotsWindow *ui;
    QSerialPort* arduino;
    PortSelection* com_window;
};

#endif // PLOTSWINDOW_H
