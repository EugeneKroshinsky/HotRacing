#ifndef SECOND_HERO_H
#define SECOND_HERO_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QRectF>
#include <QPainter>
#include <QObject>
#include <windows.h>

class SecondHero : public QGraphicsPixmapItem, public QObject
{
private:
    qreal angle;
    double speed;
public:
    explicit SecondHero();
    ~SecondHero();
    void setDefolt();
protected:
    QRectF boundingRect() const override;
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void addMyCollision(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
public slots:
    void heroMove();
};

#endif // SECOND_HERO_H*/
