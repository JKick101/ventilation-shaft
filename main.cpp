#include "wentil.h"
#include "panelwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    panelWidget *panel = new panelWidget;

    panel->setWindowTitle(QObject::tr("Контрольная панель"));
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    panel->resize(360,150);
    panel->setGeometry(QRect(screenGeometry.width()/1.5,screenGeometry.height()/3,310,150));
    panel->setMaximumSize(360,150);
    panel->setMinimumSize(360,150);
    panel->show();


    return a.exec();
}
