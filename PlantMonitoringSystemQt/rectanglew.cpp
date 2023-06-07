
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
    QImage thermo(":/images/termometr.png");
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

    //drawing numeric value of temperatureQFont font = painter.font();
    painter.translate(0, thermo.height()/2);
    QFont font = painter.font();
    constexpr int pix_size = 30;
    font.setPixelSize(pix_size);
    painter.setFont(font);
    QString _temp = QString::number(temperature) + QChar(0x00B0) + 'C';
    QFontMetrics fontMetrics(font);
    QRect textRect = fontMetrics.boundingRect(_temp);
    painter.drawText(-textRect.size().width(), 0, _temp);

    QMargins left_margin(textRect.size().width()*2,0,0,0);
    setMinimumSize(thermo.size().grownBy(left_margin));
}

void RectangleW::setHeight(int _height) {
    height = _height;
    update();
}

void RectangleW::changeHeight(int _temperature){
    // normalization needed
    setHeight(-195 * _temperature / 100);
    temperature = _temperature;
}
