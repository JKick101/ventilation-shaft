#ifndef CONNECT_H
#define CONNECT_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QRegExpValidator>
#include <QMessageBox>
#include <cstring>
#include <modbus-private.h>
#include <cstdio>
#include <QString>
#include <iostream>
#include <QTimer>
#include "panelwidget.h"

 class panelWidget;
class Connect : public QWidget
{
    Q_OBJECT
   // friend class panelWidget;
public:
    explicit Connect(QWidget *parent = 0);
    ~Connect();
       double PowerWent = 9999;
       modbus_t *ctx;
       double inShahta;
       int outside;
signals:

public slots:
   void Connection();
   void Read();
   void Write();
private:
    QLabel* IpLab;
    QLabel* PortLab;
    QLineEdit* IpEdit;
    QLineEdit* PortEdit;
    QGridLayout *grid;
    QPushButton *button;
    QMessageBox *Wbox;
    QMessageBox* Cbox;
    QMessageBox* Ibox;
    QMessageBox* Rebox;
    QMessageBox* Wrbox;
    QTimer* forRead;
    QTimer* forWrite;
};

#endif // CONNECT_H
