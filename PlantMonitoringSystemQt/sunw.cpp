
#include "sunw.h"
#include <QDebug>

SunW::SunW(QWidget *parent, int sunlightLevel)
    : QWidget{parent},
    sunlightLevel(40)
{

}

void SunW::setSunlightLevel(int level)
{
    sunlightLevel = level;
    update(); // Request a repaint of the widget
}


void SunW::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Set the background color to blue
    painter.fillRect(this->rect(), QColor(124,242,255));

    // Calculate the color of the sun based on the sunlight level
    int hue = 60;  // Yellow hue value in HSV color space
    int saturation = 50 + (200 * sunlightLevel / 100);
    int value = 255;  // Maximum brightness

    QColor sunColor = QColor::fromHsv(hue, saturation, value);

    // Draw the sun circle
    int diameter = qMin(width(), height()) / 2;
    // the size of the sun depends on the sunlight level
    diameter += ((diameter * sunlightLevel) / 100) * 0.9;
    int radius = diameter / 2;
    QPoint center = rect().center();
    painter.setPen(Qt::NoPen);
    painter.setBrush(sunColor);
    painter.drawEllipse(center, radius, radius);

    // Calculate the number of sun rays to draw
    int rayCount = (25 * sunlightLevel)/100 + 8; // depens on sunlight
    float angleStep = 360 / rayCount;
    painter.setPen(sunColor);

    // Draw the sun rays
    for (float angle = 0; angle < 360; angle += angleStep)
    {
        QPoint rayStart = center + QPoint(radius * qCos(qDegreesToRadians(angle)),
                                          radius * qSin(qDegreesToRadians(angle)));
        QPoint rayEnd = center + QPoint(radius * 1.4 * qCos(qDegreesToRadians(angle)),
                                        radius * 1.4 * qSin(qDegreesToRadians(angle)));
        painter.drawLine(rayStart, rayEnd);
    }

    // Draw the sunlight level value
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    QString sunlightText = QString::number(sunlightLevel) + "%";
    QRect textRect = QRect(center - QPoint(25, 10), center + QPoint(25, 10));
    painter.drawText(textRect, Qt::AlignCenter, sunlightText);
}
