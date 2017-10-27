#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QWidget>
#include <qcustomplot.h>
#include <QVector>
#include <vector>
#include <iostream>

class Graphic : public QWidget
{
    Q_OBJECT
public:
    explicit Graphic(QWidget *parent = 0);
    ~Graphic();

signals:

public slots:
   // void update();
    void pointGraph(double);

private:
    QCustomPlot *wGraphic;      // Объявляем объект QCustomPlot
    QCPCurve *verticalLine;     // Объявляем объект для вертикальной линии
    QCPItemTracer *tracer;      // Трасировщик по точкам графика
    QGridLayout *plot;
    QLineEdit* lineEdit;
    QTimer* timer;
    int xz = 0;
   QVector<double> x;
   QVector<double> y;





private slots:


};

#endif // GRAPHIC_H
