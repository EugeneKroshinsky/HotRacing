#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <hero.h>
#include <second_hero.h>
#include <QTimer>
#include <QDebug>
#include <dialog.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QGraphicsScene *scene;
    Hero *hero;
    QTimer *timer;
    QTimer *gameTimer;
    SecondHero *secondHero;
    Dialog dialog;

    bool isSecondHero = false;
    double time=0;
public slots:
    void updateLCD();
protected:
    void drawFigure(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
    void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
private slots:
    void on_checkBox_clicked(bool checked);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

/*class ABOBA : public QGraphicsPixmapItem
{
public:
    ABOBA()
    {
        setPixmap(QPixmap(":/pics/CoinQuestion.png"));

    }
};*/

#endif // WIDGET_H
