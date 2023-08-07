#ifndef HERO_H
#define HERO_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QRectF>
#include <QPainter>
#include <QObject>
#include <QTimer>
#include <windows.h>
#include <QDebug>

class Hero : public QGraphicsPixmapItem, public QObject
{
private:
    qreal angle;
    double speed;
    bool isTime;
    int rounds;
public:
    explicit Hero();
    ~Hero();
    void setDefolt();
    bool getBoolTime();
    int getRounds();
protected:
    QRectF boundingRect() const override;
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void addMyCollision(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
public slots:
    void heroMove();

signals:
};


#endif // HERO_H
