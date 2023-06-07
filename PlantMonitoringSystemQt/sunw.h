
#ifndef SUNW_H
#define SUNW_H

#include <QWidget>
#include <QPainter>
#include <QtMath>

class SunW : public QWidget
{
    Q_OBJECT

public:
    SunW(QWidget *parent = nullptr, int sunlightLevel = 0);
public slots:
    void setSunlightLevel(int level);
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int sunlightLevel;
};

#endif // SUNW_H
