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
     * \param[in,out] parent
     * \param[in] file_name - name of the file with data to be visualized on the plots
     * \param[in] _idx - index of this object in QMainWindow::plot_windows vector
     * \see PortSelection
     */
    explicit PlotsWindow(QWidget *parent = nullptr, QString file_name = "", int _idx = 0);
    ~PlotsWindow();

signals:
    /*!
     * \brief signal that is emitted when a window is supposed to be changed
     * \param[in] _idx
     */
    void window_closed(int _idx);

protected:
    /**
     * @brief closeEvent
     * @param[in,out] event
     */
    void closeEvent(QCloseEvent* event) override;

private:
    Ui::PlotsWindow *ui;
    QString curr_file_name;
    int idx;
};

#endif // PLOTSWINDOW_H
