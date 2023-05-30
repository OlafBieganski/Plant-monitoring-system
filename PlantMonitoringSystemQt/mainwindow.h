#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <portselection.h>
#include <QFile>
#include <plotswindow.h>
#include <rectanglew.h>
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

signals:
    /**
     * @brief emitted when new measurements are received from an external device
     * @param[in] therm Current value of temperature
     */
    void new_values(int therm);

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
    /**
     * @brief on_actionNowa_seria_triggered
     */
    void on_actionNowa_seria_triggered();
    /**
     * @brief on_actionWybierz_serie_triggered
     */
    void on_actionWybierz_serie_triggered();
    /**
     * @brief on_actionZapisz_pomiar_triggered
     */
    void on_actionZapisz_pomiar_triggered();

public slots:
    /**
     * @brief Deletes PlotsWidget object in plots_window vector when it gets destructed
     * @param[in] _idx Index of the window that is supposed to be close.
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
