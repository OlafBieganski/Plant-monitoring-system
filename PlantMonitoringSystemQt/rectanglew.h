
#ifndef RECTANGLEW_H
#define RECTANGLEW_H

#include <QWidget>
#include <QPen>
#include <QPainter>

class RectangleW : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Creates a thermometer widget with given heith of a mercury bar.
     * @param[in,out] parent
     * @param[in] _height - height of a mercury bar.
     */
    explicit RectangleW(QWidget *parent = nullptr, int _height = 0);
    /**
     * @brief Set height of mercury bar.
     * @param[in] height
     */
    void setHeight(int height);
    /**
     * @brief Overriden drawing function.
     */
    virtual void paintEvent(QPaintEvent*) override;

public slots:
    /**
     * @brief Slot for resizing a mercury bar.
     * @param[in] _temperature - The temperature value that will determine a mercury bar height.
     */
    void changeHeight(int _temperature);

private:
    int height;
    int temperature = 0;
};

#endif // RECTANGLEW_H
