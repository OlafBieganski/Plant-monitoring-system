#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <portselection.h>
#include <QFile>
#include <plotswindow.h>
#include <QLabel>
#include <QPixmap>
#include<QDateTime>

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

    void on_actionNowa_seria_triggered();

    void on_actionWybierz_serie_triggered();

    void on_actionZapisz_pomiar_triggered();

public slots:
    /**
     * @brief Deletes PlotsWidget object in plots_window vector when it gets destructed
     */
    void when_PlotsWindow_closed(int _idx);

private:
    Ui::MainWindow *ui;
    QLabel* file_info;
    QPixmap* plantPicture;
    QSerialPort* serial;
    char* serial_buffer;
    int buffer_size;
    PortSelection* com_window;
    QMap<int ,PlotsWindow*> plot_windows;
    QString curr_filename;
    int temperature, humidity, ground, sunlight;
    QDateTime measureDateTime;
    QPixmap* thermo;

    QString getFilename(const QString& path);
};
#endif // MAINWINDOW_H
