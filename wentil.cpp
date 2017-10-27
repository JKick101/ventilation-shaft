#include "wentil.h"
#include <QtGui>
#include <cmath>
#include <QtWidgets>
#include <stdio.h>
#include <math.h>
#include <mmsystem.h>
#include <cstdlib>
#include <panelwidget.h>

const int MaxAlpha = 360;
const int MinAlpha = 0;
static double alpha = MinAlpha;
static double alpha2 = MaxAlpha;
wentil::wentil(QWidget *parent)
    : QMainWindow(parent)
{

    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(update()));
    image = new QPixmap("C:\\QtProjects\\went\\poroda4.png");



}

void wentil::ChangeTime(double time)
{
    updateTimer->start(time);
}



void wentil::paintEvent(QPaintEvent * /* event */)
{


 QPainter painter(this);

 painter.setRenderHint(QPainter::Antialiasing, true);

 int side = qMin(width(), height());


 painter.setViewport((width() - side) / 2, (height() - side) / 2,
                     side, side);
 painter.setWindow(0, 0, 300, 300);


    alpha=alpha+3;
    if(alpha > MaxAlpha)
        alpha = MinAlpha;
    alpha2 = alpha2-3;
    if(alpha2 < MinAlpha)
        alpha2 = MaxAlpha;

    draw(&painter);

}

/*void wentil::mousePressEvent(QMouseEvent *event)
{

    //QPointF point = event->pos() - rect().center();

    //double theta = std::atan2(-point.x(), -point.y());

    QMessageBox msg;
        QString str;
        msg.setText(str.setNum(theta));
        msg.exec();


}
*/



void wentil::draw(QPainter *painter)
{


      //отрисовка земли
     QRadialGradient earth(150, 60, 250, 150, 60);
     painter->setPen(Qt::NoPen);
     earth.setColorAt(0.4,QColor(156,78,0));
      earth.setColorAt(0.9,QColor(77,34,14));
    painter->setBrush(earth);
    painter->drawRect(0, 60, 300, 220);


        //отрисовка левой части шахты
        QRadialGradient firstGrad(20,40,100,20,40);

         painter->setPen(QPen(Qt::black, 0.1));
         firstGrad.setColorAt(0.2, QColor(153,167,178));
         firstGrad.setColorAt(0.4, QColor(142,157,169));
         firstGrad.setColorAt(0.6, QColor(130,147,161));
         firstGrad.setColorAt(0.8, QColor(118,137,152));
         firstGrad.setColorAt(0.9, QColor(107,127,142));
         firstGrad.setColorAt(1.0, QColor(111,130,138));
          painter->setBrush(firstGrad);
           painter->drawRoundRect(20, 20, 40, 50);//левый квадрат
           painter->drawRect(20, 60, 40, 140);//левая шахта


           //отрисовка правой части шахты
          QRadialGradient secondGrad(220,60,100,220,60);
          secondGrad.setColorAt(0.2, QColor(153,167,178));
          secondGrad.setColorAt(0.4, QColor(142,157,169));
          secondGrad.setColorAt(0.6, QColor(130,147,161));
          secondGrad.setColorAt(0.8, QColor(118,137,152));
          secondGrad.setColorAt(0.9, QColor(107,127,142));
          secondGrad.setColorAt(1.0, QColor(111,130,138));
           painter->setBrush(secondGrad);
          painter->drawRoundRect(210, 20, 40, 50);//правый квадрат
          painter->drawRect(210,60,40,140);//правая шахта


           //отрисовка основания
         QRadialGradient osnovGrad(150,80,250,150,80);
         osnovGrad.setColorAt(0.7, QColor(111,130,138));
         osnovGrad.setColorAt(0.8, QColor(83,99,106));
         osnovGrad.setColorAt(0.9, QColor(74,88,94));
         painter->setPen(Qt::NoPen);
         painter->setBrush(osnovGrad);
         painter->drawRoundRect(20, 160, 230, 60);//основание





    QRadialGradient haloGradient(40, 40, 20, 40, 40);
    haloGradient.setColorAt(0.4, Qt::black);
    haloGradient.setColorAt(0.9, Qt::darkGray);
    haloGradient.setColorAt(1.0, Qt::lightGray);
    haloGradient.setColorAt(0.4, Qt::white);
    painter->setPen(Qt::NoPen);
    painter->setBrush(haloGradient);
    painter->drawEllipse(20, 20, 40, 40);



    //QPen thinPen(palette().foreground(), 0.3);



   double X1= cos(alpha/180*3.14)*18+40;
   double Y1=sin(alpha/180*3.14)*18+40;
   double X2=cos(alpha/180*3.14+0.8)*18+40;
   double Y2=sin(alpha/180*3.14+0.8)*18+40;


   double X3= cos(alpha/180*3.14-2.09)*18+40;
   double Y3=sin(alpha/180*3.14-2.09)*18+40;
   double X4=cos(alpha/180*3.14+0.8-2.09)*18+40;
   double Y4=sin(alpha/180*3.14+0.8-2.09)*18+40;

   double X5= cos(alpha/180*3.14+2.09)*18+40;
   double Y5=sin(alpha/180*3.14+2.09)*18+40;
   double X6=cos(alpha/180*3.14+0.8+2.09)*18+40;
   double Y6=sin(alpha/180*3.14+0.8+2.09)*18+40;




    int triangle[3][2] = {
     { static_cast<int>(X1), static_cast<int>(Y1) }, { static_cast<int>(X2), static_cast<int>(Y2) }, { 40, 40 }
   };
    int triangle1[3][2] = {
     { static_cast<int>(X3), static_cast<int>(Y3) }, { static_cast<int>(X4), static_cast<int>(Y4) }, { 40, 40 }
   };
    int triangle2[3][2] = {
     { static_cast<int>(X5), static_cast<int>(Y5) }, { static_cast<int>(X6), static_cast<int>(Y6) }, { 40, 40 }
   };

    //painter->setPen(thinPen);
    painter->setBrush(Qt::darkGray);
    painter->drawPolygon(QPolygon(3, &triangle[0][0]));
    painter->drawPolygon(QPolygon(3, &triangle1[0][0]));
   painter->drawPolygon(QPolygon(3, &triangle2[0][0]));



    //отрисовка градиента для вентилятора1
   QRadialGradient Gradient(40, 40, 2, 40, 40);

   Gradient.setColorAt(1.0, Qt::black);
   Gradient.setColorAt(0.3, Qt::lightGray);
   Gradient.setColorAt(0.5, Qt::darkGray);
   Gradient.setColorAt(0.8, Qt::white);


   painter->setPen(Qt::NoPen);
   painter->setBrush(Gradient);
   painter->drawEllipse(36, 36, 8, 8);


    //отрисовка градиента для вентилятора2
   QRadialGradient wentGradient(230, 40, 20, 230, 40);


   wentGradient.setColorAt(0.4, Qt::black);
   wentGradient.setColorAt(0.9, Qt::darkGray);
   wentGradient.setColorAt(1.0, Qt::lightGray);
   wentGradient.setColorAt(0.4, Qt::white);

   painter->setPen(Qt::NoPen);
   painter->setBrush(wentGradient);
   painter->drawEllipse(210, 20, 40, 40);


    //изменене координат теругольников
   double XA1= cos(alpha2/180*3.14)*18+230;
   double YA1=sin(alpha2/180*3.14)*18+40;
   double XA2=cos(alpha2/180*3.14+0.8)*18+230;
   double YA2=sin(alpha2/180*3.14+0.8)*18+40;


   double XA3= cos(alpha2/180*3.14-2.09)*18+230;
   double YA3=sin(alpha2/180*3.14-2.09)*18+40;
   double XA4=cos(alpha2/180*3.14+0.8-2.09)*18+230;
   double YA4=sin(alpha2/180*3.14+0.8-2.09)*18+40;

   double XA5= cos(alpha2/180*3.14+2.09)*18+230;
   double YA5=sin(alpha2/180*3.14+2.09)*18+40;
   double XA6=cos(alpha2/180*3.14+0.8+2.09)*18+230;
   double YA6=sin(alpha2/180*3.14+0.8+2.09)*18+40;




    int triangleA[3][2] = {
     { static_cast<int>(XA1), static_cast<int>(YA1) }, { static_cast<int>(XA2), static_cast<int>(YA2) }, { 230, 40 }
   };
    int triangleA1[3][2] = {
     { static_cast<int>(XA3), static_cast<int>(YA3) }, { static_cast<int>(XA4), static_cast<int>(YA4) }, { 230, 40 }
   };
    int triangleA2[3][2] = {
     { static_cast<int>(XA5), static_cast<int>(YA5) }, { static_cast<int>(XA6), static_cast<int>(YA6) }, { 230, 40 }
   };

    //painter->setPen(thinPen);
    painter->setBrush(Qt::darkGray);
    painter->drawPolygon(QPolygon(3, &triangleA[0][0]));
    painter->drawPolygon(QPolygon(3, &triangleA1[0][0]));
   painter->drawPolygon(QPolygon(3, &triangleA2[0][0]));


   QRadialGradient wentGradient2(230, 40, 2, 230, 40);

   wentGradient2.setColorAt(1.0, Qt::black);
   wentGradient2.setColorAt(0.3, Qt::lightGray);
   wentGradient2.setColorAt(0.5, Qt::darkGray);
   wentGradient2.setColorAt(0.8, Qt::white);


   painter->setPen(Qt::NoPen);
   painter->setBrush(wentGradient2);
   painter->drawEllipse(226, 36, 8, 8);
 //painter->drawPixmap(QPointF(130,200), *image, QRect(10, 10, 20,20));
   painter->drawPixmap(50,180,170,40, *image);


}




wentil::~wentil()
{

}
