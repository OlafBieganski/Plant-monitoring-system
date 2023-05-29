
#ifndef RECTANGLEW_H
#define RECTANGLEW_H

#include <QWidget>
#include <QPen>
#include <QPainter>

class RectangleW : public QWidget
{
    Q_OBJECT
public:
    explicit RectangleW(QWidget *parent = nullptr, int _height = 0);
    void setHeight(int height);
    virtual void paintEvent(QPaintEvent*) override;

public slots:
    void changeHeight(int _newHeight);

private:
    int height;

};

#endif // RECTANGLEW_H
