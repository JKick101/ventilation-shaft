#include "graphic.h"

Graphic::Graphic(QWidget *parent) :
    QWidget(parent)
{
    plot = new QGridLayout(this);
    lineEdit = new QLineEdit;
    wGraphic = new QCustomPlot();
    timer = new QTimer;
    timer->start(500);
    wGraphic->setGeometry(0,0,700,400);
    x.resize(1000);
    y.resize(1000);
     this->setWindowTitle(QObject::tr("График"));
     wGraphic->setInteraction(QCP::iRangeZoom,true);
     wGraphic->setInteraction(QCP::iRangeDrag, true);
    // wGraphic->axisRect()->setRangeDrag(Qt::Horizontal);   // Включаем перетаскивание только по горизонтальной оси
    // wGraphic->axisRect()->setRangeZoom(Qt::Horizontal);
     wGraphic->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
     wGraphic->yAxis->setTickLabelFont(QFont(QFont().family(), 8));

    // Инициализируем вертикальную линию
    verticalLine = new QCPCurve(wGraphic->xAxis, wGraphic->yAxis);

    // Подключаем сигналы событий мыши от полотна графика к слотам для их обработки
    connect(timer, SIGNAL(timeout()),this,SLOT(update()));

    // создаём вектора для вертикальной линии


    wGraphic->addPlottable(verticalLine);   // Добавляем линию на полотно


    // Добавляем график на полотно
    wGraphic->addGraph(wGraphic->xAxis, wGraphic->yAxis);
    wGraphic->graph(0)->setData(x,y);     // Устанавливаем координаты точек графика



    // Подписываем оси координат
    wGraphic->xAxis->setLabel("Секунды");
    wGraphic->yAxis->setLabel("Температура в шахте");

    // Устанавливаем максимальные и минимальные значения координат
    wGraphic->xAxis->setRange(0,1000);
    wGraphic->yAxis->setRange(0,50);

    plot->addWidget(wGraphic,0,0);
   // plot->addWidget(lineEdit,1,0);
    this->setGeometry(500,500,700,400);
    // Отрисовываем содержимое полотна
    wGraphic->replot();


}


void Graphic::pointGraph(double temp)
{


    for (int i = 0 ;i < 999 ;i++)
      {
        x[i] = x[i+1];
        y[i] = y[i+1];
      }
    x[999] = x[998]+1;
    y[999] = temp;
    if (x[999] >= (1000+xz) )
    {
        xz+=1;
     wGraphic->xAxis->setRange(0+xz,1000+xz);
     }
     verticalLine->setData(x, y);
   // lineEdit->setText(QString::number(y[0])+"  "+QString::number(x[1])+
      //      "  "+QString::number(y[2])+"  "+QString::number(y[3])+"  "+QString::number(y[4]));
    wGraphic->replot();
}


Graphic::~Graphic()
{

}
