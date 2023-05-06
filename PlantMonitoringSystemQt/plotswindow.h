#ifndef PLOTSWINDOW_H
#define PLOTSWINDOW_H

#include <QMainWindow>

namespace Ui {
class PlotsWindow;
}

class PlotsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlotsWindow(QWidget *parent = nullptr);
    ~PlotsWindow();

signals:
    void switch_window();
    void change_serial_port();

private slots:
    void on_actionWybierz_port_szeregowy_triggered();

    void on_actionOkno_g_wne_triggered();

private:
    Ui::PlotsWindow *ui;
};

#endif // PLOTSWINDOW_H
