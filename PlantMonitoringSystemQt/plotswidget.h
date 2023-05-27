#ifndef PLOTSWIDGET_H
#define PLOTSWIDGET_H

#include <QWidget>
#include <QSerialPort>

namespace Ui {
class PlotsWidget;
}

class PlotsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlotsWidget(QWidget *parent = nullptr, QString file_name = nullptr, int _idx = -1);
    ~PlotsWidget();

private:
    Ui::PlotsWidget *ui;
    QString curr_file_name;
    int idx;

signals:
    /*!
     * \brief signal that is emitted when a window is supposed to be changed
     */
    void window_closed(int _idx);
};

#endif // PLOTSWIDGET_H
