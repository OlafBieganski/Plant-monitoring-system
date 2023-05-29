
#include "rectanglew.h"

RectangleW::RectangleW(QWidget *parent, int _height)
    : QWidget{parent},
    height(_height)
{

}

void RectangleW::paintEvent(QPaintEvent*){
    QPainter painter(this);

    // Set the initial rectangle properties
    QRect rectangle(17, 203, 34, height);
    QColor fillColor(Qt::red);
    QPen pen(Qt::red);
    QImage thermo("C:/Users/olafb/Downloads/termometr");
    setMinimumSize(thermo.size());
    // setStyleSheet("background: rgb(64, 202, 217);"); ???

    //translete the base of the coordinate system
    int x_offset = width()/2 - thermo.width()/2;
    int y_offset = QWidget::height()/2 - thermo.height()/2;
    painter.translate(x_offset, y_offset);
    // Draw the rectangle
    painter.setPen(pen);
    painter.setBrush(fillColor);
    painter.drawRect(rectangle);
    painter.drawImage(0, 0, thermo);
}

void RectangleW::setHeight(int _height) {
    height = _height;
    update();
}

void RectangleW::changeHeight(int _newHeight){
    // normalization needed
    setHeight(-195 * _newHeight / 100);
}
