#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <portselection.h>
#include <plotswindow.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /*!
     * \brief creates connection with a serial port and receives data
     */
    void on_pushButton_measure_clicked();
    /*!
     * \brief on_actionWybierz_port_szeregowy_triggered
     */
    void on_actionWybierz_port_szeregowy_triggered();
    /*!
     * \brief on_actionWykresy_triggered
     */
    void on_actionWykresy_triggered();
    /*!
     * \brief onSecondWindowClosed
     */
    void onSecondWindowClosed();

private:
    Ui::MainWindow *ui;
    QSerialPort* serial;
    char* serial_buffer;
    int buffer_size;
    PortSelection* com_window;
    PlotsWindow* second_window = nullptr;
};
#endif // MAINWINDOW_H
