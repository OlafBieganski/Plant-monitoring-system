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
     * \brief Creates a PlotsWindow object.
     * \param[in,out] parent
     * \param[in] file_name - name of the file with data to be visualized on the plots.
     * \param[in] _idx - index of this object in QMainWindow::plot_windows vector.
     * \see PortSelection
     */
    explicit PlotsWindow(QWidget *parent = nullptr, QString file_name = "", int _idx = 0);
    ~PlotsWindow();
    /**
     * @brief Overriden drawing function.
     */
    virtual void paintEvent(QPaintEvent*) override;

signals:
    /*!
     * \brief Signal that is emitted when a window is supposed to be changed.
     * \param[in] _idx - the index of a closed window. Needed for a deletion in QMap<int ,PlotsWindow*> plot_windows.
     */
    void window_closed(int _idx);

public slots:
    /**
     * @brief repaint a widget when a translation is updated
     */
    void when_lang_update();

protected:
    /**
     * @brief Overriden funtion that defines a drawing procedure.
     * @param[in,out] event
     */
    void closeEvent(QCloseEvent* event) override;

private:
    Ui::PlotsWindow *ui;
    QString curr_file_name;
    int idx;
};

#endif // PLOTSWINDOW_H
