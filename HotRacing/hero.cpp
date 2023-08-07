#include <hero.h>
#define HERO_BOOST 0.4
#define HERO_SLOWDOWN 0.15

Hero::Hero() : QGraphicsPixmapItem()
{
    angle = 0;
    speed = 0;
    rounds = 0;
    isTime = false;
    setRotation(angle);
    QPixmap skinPlayerOne = QPixmap(":/pics/pixelPlayer1.png");
    setPixmap(skinPlayerOne);
    setOffset(-11, -18.5);
}

Hero::~Hero()
{

}

QRectF Hero::boundingRect() const
{
    return QRectF(-11,-18.5, 22, 48);
}

/*void Hero::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon polygon;
    polygon << QPoint(0,-20) << QPoint(12,20) << QPoint(-12,20);
    painter->setBrush(Qt::yellow);
    painter->drawPolygon(polygon);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}*/

void Hero::addMyCollision(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    //коллизия препядствий
    if(this->x()+10 > x1 && this->x() < x1+5 && this->y()>y1&&this->y()<y3)
      {
        this->setX(x1-10);
          speed = 5;
      }
    if(this->x()-10 < x2 && this->x() > x2-5 && this->y()>y1 &&this->y()<y3)
      {
        this->setX(x2+10);
          speed = 5;
      }
    if(this->y()-10<y3 && this->y() > y3-5 && this->x()>x1 &&this->x()<x2)
       {
         this->setY(y3+10);
           speed = 5;
       }
    if(this->y()+10>y1 && this->y()<y1+5 && this->x()>x1 &&this->x()<x2)
       {
         this->setY(y1-10);
           speed = 5;
       }
    Q_UNUSED(y2);
    Q_UNUSED(x3);
    Q_UNUSED(x4);
    Q_UNUSED(y4);
}

void Hero::setDefolt()
{
    angle = 0;
    setRotation(angle);
    speed = 0;
    rounds = 0;
    isTime = false;
}

bool Hero::getBoolTime()
{
    return isTime;
}

int Hero::getRounds()
{
    return rounds;
}

void Hero::heroMove()
{
  //таймер круга
  if(this->y()> -5 && this->y() < 5 && this->x()>-700 && this->x()<-540 && rounds!=3)
  {
        isTime = true;
        rounds++;
  }
  else if(this->y()> -5 && this->y() < 5 && this->x()>-700 && this->x()<-540 && rounds==3)
  {
      isTime = false;
      rounds=0;
  }
  //события для клавиш
  if(GetAsyncKeyState(VK_LEFT))
  {
      angle -=10;
      setRotation(angle);
      if(speed>0) speed-=HERO_SLOWDOWN;
  }
  if(GetAsyncKeyState(VK_RIGHT))
  {
      angle +=10;
      setRotation(angle);
      if(speed>0) speed-=HERO_SLOWDOWN;
  }
  if(GetAsyncKeyState(VK_UP))
  {
      setPos(mapToParent(0, -speed));
      if(speed<13)
      {
          speed+=HERO_BOOST;
      }
      else
      {
          setPixmap(QPixmap(":/pics/pixelPlayer1Frame2.png"));
      }
  }
  if(GetAsyncKeyState(VK_DOWN))
  {
      setPos(mapToParent(0, 5));
      speed = 0;
  }
  if(!(GetAsyncKeyState(VK_UP)||GetAsyncKeyState(VK_DOWN)) && speed>0)
  {
      setPos(mapToParent(0, -speed));
      speed-=HERO_SLOWDOWN;
  }
  if(speed<13 ) setPixmap(QPixmap(":/pics/pixelPlayer1.png"));
  //прописываем стенки
  if(this->x() - 10 <-700)
  {
      this->setX(-690);
      speed=5;
  }
  if(this->x() +10 >700)
  {
      this->setX(690);
      speed=5;
  }
  if(this->y() - 10 <-350)
  {
      this->setY(-340);
      speed=5;
  }
  if(this->y() + 10 >350)
  {
      this->setY(340);
      speed=5;
  }
  //коллизия препятствий
  addMyCollision(0, -130, 280, -130, 280, 150, 0, 150);
  addMyCollision(-540, 70,0, 70, 0, 150, -540, 150);
  addMyCollision(280, 75, 540, 75, 540, 150, 280, 150);
  addMyCollision(140, 280, 440, 280, 440, 350, 140, 350);
  addMyCollision(-540, -150, -440, -150, -440, 260, -540, 260);
  addMyCollision(-320, -350, -250, -350, -250, 0, -320, 0);
  addMyCollision(350, -350, 700, -350, 700, -100, 350, -100);
  addMyCollision(-270, 220, -200, 220, -200, 290, -270, 290);
  addMyCollision(-700, -350, 700, -350, 700, 350, -700, 350);
}
