#ifndef WENTIL_H
#define WENTIL_H

#include <QMainWindow>
#include <QAction>

class panelWidget;
class wentil : public QMainWindow
{
    Q_OBJECT

friend class panelWidget;

protected:
    void paintEvent(QPaintEvent *event);
    //void mousePressEvent(QMouseEvent *event);

public:
    void draw(QPainter*);
    QTimer *updateTimer;
     panelWidget *panel;
      QPixmap *image;

public:
    wentil(QWidget *parent = 0);
    ~wentil();
    void ChangeTime(double);
private:

};

#endif // WENTIL_H
