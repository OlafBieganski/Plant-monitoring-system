
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
     * @brief RectangleW
     * @param[in,out] parent
     * @param[in] _height
     */
    explicit RectangleW(QWidget *parent = nullptr, int _height = 0);
    /**
     * @brief setHeight
     * @param[in] height
     */
    void setHeight(int height);
    /**
     * @brief paintEvent
     */
    virtual void paintEvent(QPaintEvent*) override;

public slots:
    /**
     * @brief changeHeight
     * @param[in] _temperature
     */
    void changeHeight(int _temperature);

private:
    int height;
    int temperature = 0;
};

#endif // RECTANGLEW_H
