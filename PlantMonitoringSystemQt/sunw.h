
#ifndef SUNW_H
#define SUNW_H

#include <QWidget>
#include <QPainter>
#include <QtMath>

class SunW : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Creates a SunW object that visualizes a sunlight level.
     * @param parent
     * @param sunlightLevel - determines a brithnes of a sun widget and a number of beams. Range: <0; 100>.
     */
    SunW(QWidget *parent = nullptr, int sunlightLevel = 0);
public slots:
    /**
     * @brief Updates a value of sunlightLevel.
     * @param level - Range: <0; 100>.
     */
    void setSunlightLevel(int level);
protected:
    /**
     * @brief Overriden drawing function.
     * @param event
     */
    void paintEvent(QPaintEvent *event) override;

private:
    int sunlightLevel;
};

#endif // SUNW_H
