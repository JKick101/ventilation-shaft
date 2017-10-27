#ifndef PANELWIDGET_H
#define PANELWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QtGui>
#include <QMenuBar>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <iostream>
#include <QGraphicsItem>
#include "connect.h"
#include <QTimer>
#include <winsock2.h>
#include <windows.h>
#include <windowsx.h>
#include <QAction>
#include "graphic.h"

#define Cv 0.715E03
#define Pv 1.225
#define R 8.31
#define V 6.8965
#define Vs 200
#define Ln 2.56
#define MaxPower 4095
#define MaximumTemp 50
#define Kontroller 65535

using namespace std;

class wentil;
class Connect;
class Graphic;

class panelWidget : public QWidget
{
    Q_OBJECT
    friend class wentil;
    friend class Connect;
    friend class Graphic;
public:
    explicit panelWidget(QWidget *parent = 0);
    ~panelWidget();
    double roundTo(double , int );


    QMenu *connectMenu;
    QMenu *showMod;
    QMenu* showGraph;
    QMenuBar *bar;
    wentil *went = nullptr;
    Connect *con = nullptr;
    Graphic *graph = nullptr;
    QMenu *Out;

 QTimer *ForRead;
 QTimer *ForComp;
 QTimer *ForWrite;

    QGridLayout *grid;

signals:


public slots:
    void newConnection();
    void showModel();
    void ChangeTimer(wentil* Went,double time);
    void out();
    void Read();
    void Computing();
    void WriteTemp();
    void showgraph();
protected :


private:

    QSlider *TempOut;
    QSlider *TempPor;
    QLabel *TempIn;
    QLabel *PowerWent;
    QHBoxLayout *Slider;
    QHBoxLayout *Label;
    QVBoxLayout *Vert;
    QLabel *TempLOut;
    QLabel *TempLPor;
    QLineEdit *ETempIN;
    QLineEdit *EPowerWent;
    QSpinBox *ToTempPor;
    QSpinBox *ToTempOut;

    QMessageBox* Qbox;

     double tempInShahta = 0.0;


};


#endif // PANELWIDGET_H
