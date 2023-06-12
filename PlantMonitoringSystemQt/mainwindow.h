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
#include <sunw.h>
#include <QInputDialog>
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    /**
     * @brief Overriden drawing function.
     */
    void paintEvent(QPaintEvent*) override;

protected:
    void resizeEvent(QResizeEvent *event) override;

signals:
    /**
     * @brief emitted when new measurements are received from an external device
     * @param[in] therm - Current value of temperature
     */
    void new_temp(int therm);
    /**
     * @brief emitted when new measurements are received from an external device
     * @param[in] _sunlight - new value of the sunlight level
     */
    void new_sun(int _sunlight);
    /**
     * @brief lang_update
     */
    void lang_update();

private slots:
    /*!
     * \brief creates a connection with a serial port and receives data
     */
    void on_pushButton_measure_clicked();
    /*!
     * \brief show a window with a serial port connection configuration
     */
    void on_actionWybierz_port_szeregowy_triggered();
    /*!
     * \brief show a new window with plots and the data from a current file
     */
    void on_actionWykresy_triggered();
    /**
     * @brief creates a new file for a measurement data
     */
    void on_actionNowa_seria_triggered();
    /**
     * @brief Set a series file choosen by the user as an active one
     */
    void on_actionWybierz_serie_triggered();
    /**
     * @brief Insert the data from serial port to an active series file
     */
    void on_actionZapisz_pomiar_triggered();

    void on_actionJ_zyk_Language_triggered();

public slots:
    /**
     * @brief Deletes PlotsWidget object in plots_window vector when it gets destructed
     * @param[in] _idx Index of the window that is supposed to be close.
     */
    void when_PlotsWindow_closed(int _idx);

private:
    Ui::MainWindow *ui;
    QLabel* file_info;
    QPixmap plantPicture;
    QSerialPort* serial;
    char* serial_buffer;
    int buffer_size;
    PortSelection* com_window;
    QMap<int ,PlotsWindow*> plot_windows;
    QString curr_filename;
    int temperature, humidity, ground, sunlight;
    QDateTime measureDateTime;
    QPixmap* thermo;
    QTranslator* lang;

    QString getFilename(const QString& path);
};
#endif // MAINWINDOW_H
