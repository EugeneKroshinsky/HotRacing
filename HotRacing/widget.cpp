#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    dialog.setModal(true);
    dialog.show();

    this->resize(1500, 800);
    this->setFixedSize(1500, 800);

    scene = new QGraphicsScene();


    hero = new Hero();

    QPixmap b = hero->pixmap();

    scene->setSceneRect(-250,-250,500,500);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene->addLine(-700, 350, -700, -350, QPen(Qt::red));
    scene->addLine(700, 350, 700, -350, QPen(Qt::red));
    scene->addLine(-700, -350, 700, -350, QPen(Qt::red));
    scene->addLine(700, 350, -700, 350, QPen(Qt::red));

    //РИСУЕМ КАРТУ
    QColor color(Qt::green);
    drawFigure(0, -130, 280, -130, 280, 150, 0, 150);
    drawFigure(-540, 70,0, 70, 0, 150, -540, 150);
    drawFigure(280, 75, 540, 75, 540, 150, 280, 150);
    drawFigure(140, 280, 440, 280, 440, 350, 140, 350);
    drawFigure(-540, -150, -440, -150, -440, 260, -540, 260);
    drawFigure(-320, -350, -250, -350, -250, 0, -320, 0);
    drawFigure(350, -350, 700, -350, 700, -100, 350, -100);
    drawFigure(-270, 220, -200, 220, -200, 290, -270, 290);

    //старт/финиш
    for(int i=0; i<8; i++)
         scene->addRect(-540-i*20, -10, -10, 10, QPen(Qt::white),QBrush(Qt::white));
    for(int i=0; i<8; i++)
         scene->addRect(-550-i*20, 0, -10, 10, QPen(Qt::white),QBrush(Qt::white));
    for(int i=0; i<8; i++)
         scene->addRect(-540-i*20, 0, -10, 10, QPen(Qt::black),QBrush(Qt::black));
    for(int i=0; i<8; i++)
         scene->addRect(-550-i*20, -10, -10, 10, QPen(Qt::black),QBrush(Qt::black));

    ui->graphicsView->setBackgroundBrush(QColor(Qt::gray));
    ui->graphicsView->setScene(scene);

    //добавляем героя
    scene->addItem(hero);
    hero->setPos(-600, 100);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, hero, &Hero::heroMove);
    timer->start(1000/50);

    gameTimer = new QTimer();
    connect(gameTimer, &QTimer::timeout, this, &Widget::updateLCD);
    gameTimer->start(100);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::updateLCD()
{
    if(hero->getBoolTime())
    {
        time+=0.1;
        ui->lcdNumber->display(time);
        ui->lcdNumber_2->display(hero->getRounds()-1);
    }
    else if(time!=0)
    {
        ui->lcdNumber_3->display(time);
        ui->lcdNumber_2->display(hero->getRounds());
        time = 0;
        ui->lcdNumber->display(time);
    }
}

void Widget::drawFigure(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    QPolygon polygon;
    polygon << QPoint(x1,y1) << QPoint(x2,y2) << QPoint(x3,y3) << QPoint(x4,y4);
    scene->addPolygon(polygon, QPen(Qt::black), QBrush(Qt::green));
}

void Widget::drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{

    QPolygon polygon;
    polygon << QPoint(x1,y1) << QPoint(x2,y2) << QPoint(x3,y3);
    scene->addPolygon(polygon, QPen(Qt::black), QBrush(Qt::green));
}

void Widget::on_checkBox_clicked(bool checked)
{
    if(checked && !isSecondHero)
    {
        secondHero = new SecondHero();
        isSecondHero = true;
        scene->addItem(secondHero);
         connect(timer, &QTimer::timeout, secondHero, &SecondHero::heroMove);
        secondHero->setPos(-630, 100);
    }
    else if(!checked && isSecondHero)
    {
        delete secondHero;
        isSecondHero = false;
    }
}

void Widget::on_pushButton_clicked()
{
    hero->setPos(-600 ,100);
    hero->setDefolt();
    if(isSecondHero)
    {
        secondHero->setPos(-630, 100);
        secondHero->setDefolt();
    }
}

void Widget::on_pushButton_2_clicked()
{
    dialog.show();
}
