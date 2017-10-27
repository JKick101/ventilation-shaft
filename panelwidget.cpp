#include "panelwidget.h"
#include "wentil.h"
static int  K=1;
panelWidget::panelWidget(QWidget *parent) :
    QWidget(parent)
{

    connectMenu = new QMenu("Соединение");//меню соединения
    showMod = new QMenu("Показать модель");//меню модели
    showGraph = new QMenu("Показать график");
    bar = new QMenuBar(this);
    Out = new QMenu("Выход");
    TempOut = new QSlider(Qt::Horizontal);
    TempOut->setRange(7,20);
    TempPor = new QSlider(Qt::Horizontal);
    TempPor->setRange(25,40);
    TempIn = new QLabel("Температура в шахте");
    PowerWent = new QLabel("Мощность вентилятора");

    grid = new QGridLayout(this);
    Slider = new QHBoxLayout;
    Label = new QHBoxLayout;
    TempLOut = new QLabel("Температура снаружи");
    TempLPor = new QLabel("Температура руды");
    ETempIN = new  QLineEdit();
    EPowerWent = new  QLineEdit;
    ToTempPor =  new QSpinBox;
    ToTempPor->setValue(25);
    ToTempPor->setRange(25,40);
    ToTempOut = new QSpinBox;
    ToTempOut->setValue(7);
    ToTempOut->setRange(7,20);
    Vert = new QVBoxLayout;
    Qbox =new QMessageBox;
    //TempIn->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    ETempIN->setReadOnly(true);
    EPowerWent->setReadOnly(true);

    TempIn->setFixedSize(140,20);
    PowerWent->setFixedSize(140,20);
    grid->addWidget(TempIn,1,0);
    grid->addWidget(PowerWent,1,1);
    grid->addWidget(ETempIN,2,0);
    grid->addWidget(EPowerWent,2,1);
    grid->addWidget(TempLOut,3,0);
    grid->addWidget(TempLPor,3,1);

    Label->addWidget(ToTempOut);
        Label->addWidget(TempOut);
        Label->addWidget(ToTempPor);
        Label->addWidget(TempPor);
        grid->addLayout(Label,4,0,1,2);


    connectMenu->addAction("Подключиться", this, SLOT( newConnection()), Qt::CTRL+Qt::Key_C);
    connectMenu->addSeparator();

    showMod->addAction("Показать модель", this, SLOT(showModel()), Qt::CTRL+Qt::Key_M);
    showMod->addSeparator();

    Out->addAction("Выход", this, SLOT(out()), Qt::CTRL+Qt::Key_E);
    //Out->addSeparator();

    showGraph->addAction("График", this, SLOT(showgraph()),Qt::CTRL+Qt::Key_G);

        bar->addMenu(connectMenu);
        bar->addMenu(showMod);
        bar->addMenu(showGraph);
        bar->addMenu(Out);
        bar->setFixedSize(360,20);
        grid->addWidget(bar,0,0);
        bar->show();

        connect(TempOut, SIGNAL(valueChanged(int)), ToTempOut, SLOT(setValue(int)));
        connect(ToTempOut, SIGNAL(valueChanged(int)),TempOut , SLOT(setValue(int)));
        connect(TempPor, SIGNAL(valueChanged(int)), ToTempPor, SLOT(setValue(int)));
        connect(ToTempPor, SIGNAL(valueChanged(int)),TempPor , SLOT(setValue(int)));

}
panelWidget::~panelWidget()
{

}


void panelWidget::showModel()
{
   went = new wentil;
    went->setWindowTitle(QObject::tr("Шахта"));
    //went->resize(300, 300);
    went->setMaximumSize(500,500);
    went->setMinimumSize(500,500);
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
   went->setGeometry(QRect(screenGeometry.width()/screenGeometry.width()*100,screenGeometry.height()/screenGeometry.height()*100,400,400));
    //grid->addWidget(went,5,0,1,2);
    //this->setGeometry(QRect(300,200,500,600));

   went->show();

}

void panelWidget::newConnection()
{
    con = new Connect;
    ForRead = new QTimer(this);
    ForComp = new QTimer(this);
    ForWrite = new QTimer(this);
    con->setWindowTitle(QObject::tr("Connection Window"));
     this->setMaximumSize(360,350);
    con->setMaximumSize(360,200);
   con->setMinimumSize(360,200);
    connectMenu->setDisabled(true);

    grid->addWidget(con,5,0,1,2);
    con->show();
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
   this->setGeometry(QRect(screenGeometry.width()/1.5,screenGeometry.height()/3,310,450));
    connect(ForRead, SIGNAL(timeout()), this, SLOT(Read()));
    ForRead->start(100);
    connect(ForComp, SIGNAL(timeout()), this, SLOT(Computing()));
    connect(ForWrite, SIGNAL(timeout()), this, SLOT(WriteTemp()));
}



void panelWidget::showgraph()
{
    graph = new Graphic;
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    graph->setGeometry(QRect(screenGeometry.width()/screenGeometry.width()*100,screenGeometry.height()/screenGeometry.height()*100,600,400));
    graph->show();
}



void panelWidget::ChangeTimer(wentil* Went,double time)
{
    Went->ChangeTime(time);


}
void panelWidget::out()
{
    /*Qbox->setWindowTitle("EXIT");
    Qbox->setText("Dou you want to exit?");
    QPushButton *Out = Qbox->addButton(tr("Ok"), QMessageBox::YesRole);
    QPushButton *Cancel = Qbox->addButton(tr("Cancel"),QMessageBox::NoRole);
    Qbox->setIcon(QMessageBox::Question);
    int result = Qbox->show();
    if (result == 5)
   {*/


        if (went || graph )
            if (went && graph )
            {
                graph->~Graphic();
                went->~wentil();
                close();
            }

            else if(graph)
                    {
                        graph->~Graphic();
                        close();
                    }
                 else
                    {
                        went->~wentil();
                        close();
                    }
        else
        {
            close();
        }


   // }

   // delete Out;
   // delete Cancel;
}

void panelWidget::Read()
{


    if (con->PowerWent != 9999)
    {
        EPowerWent->setText(QString::number(this->roundTo((con->PowerWent/MaxPower/*Kontroller*/*100),2))+"%");

        if (K == 1)
        {
         tempInShahta = ToTempPor->value();
         Computing();
         K=0;
        }

     }
   if (went != nullptr && con != nullptr && con->PowerWent != 9999)
   {
        ChangeTimer(went,this->roundTo((100/(con->PowerWent/MaxPower/*Kontroller*/*100)),2));

    }

}


void panelWidget::Computing()
{

tempInShahta = tempInShahta + 5*((V*R*5/2*(ToTempPor->value()-tempInShahta))/(Pv*Vs*Cv)-((3.0/100*(con->PowerWent/MaxPower/*Kontroller*/*100))*Pv*Cv*(tempInShahta-ToTempOut->value()))/(Pv*Vs*Cv));



QString str;
    /*if (tempInShahta < ToTempOut->value())
       tempInShahta = ToTempOut->value();
   if (tempInShahta > ToTempPor->value())
       tempInShahta = ToTempPor->value();*/
   ETempIN->setText(str.setNum(this->roundTo(tempInShahta,2))+"*C");
   if (graph != nullptr && con != nullptr && con->PowerWent != 9999)
   {
        graph->pointGraph(this->roundTo(tempInShahta,2));

    }
   ForComp->start(100);
   ForWrite->start(100);
}

void panelWidget::WriteTemp()
{
    con->inShahta = tempInShahta;
    con->outside =  ToTempOut->value();
}


double panelWidget::roundTo(double inpValue, int inpCount)
{
    double outpValue;
    double tempVal;
    tempVal=inpValue*pow(10,inpCount);
    if (double(int(tempVal))+0.5==tempVal)
    {
        if (int(tempVal)%2==0)
            {outpValue=double(qFloor(tempVal))/pow(10,inpCount);}
        else
            {outpValue=double(qCeil(tempVal))/pow(10,inpCount);}
    }
    else
    {
        if (double(int(tempVal))+0.5>tempVal)
            {outpValue=double(qCeil(tempVal))/pow(10,inpCount);}
        else
            {outpValue=double(qFloor(tempVal))/pow(10,inpCount);}
    }
    return(outpValue);
}

