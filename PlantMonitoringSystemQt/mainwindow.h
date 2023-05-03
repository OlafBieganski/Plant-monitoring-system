#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

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
private:
    Ui::MainWindow *ui;

    QSerialPort* serial;
    char* serial_buffer;
    int buffer_size;
};
#endif // MAINWINDOW_H
