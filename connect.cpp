#include "connect.h"


using namespace  std;

static  char str3[16];


Connect::Connect(QWidget *parent) :
    QWidget(parent)
{

    IpLab = new QLabel("IP для соединения");
    PortLab = new QLabel("Порт для соединения");
    IpEdit = new QLineEdit;
    Cbox = new QMessageBox;
    Ibox = new QMessageBox;
    Wbox = new QMessageBox;
    Rebox = new QMessageBox;
    Wrbox = new QMessageBox;

    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";

    QRegExp ipRegex ("^" + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange + "$");


    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    IpEdit->setValidator(ipValidator);



    PortEdit = new QLineEdit;
    grid = new QGridLayout(this);
    button = new QPushButton("Соединение");
     connect(button, SIGNAL(clicked()),this,SLOT(Connection()));

    grid->setColumnStretch(2,10);
     grid->addWidget(IpLab,0,0);
      grid->addWidget(PortLab,1,0);
       grid->addWidget(IpEdit,0,1);
        grid->addWidget(PortEdit,1,1);
        grid->addWidget(button,2,1);

        forRead = new QTimer(this);
        connect(forRead, SIGNAL(timeout()),this,SLOT(Read()));
        forWrite = new QTimer(this);
        connect(forWrite, SIGNAL(timeout()),this,SLOT(Write()));

}

Connect::~Connect()
{

}

void Connect::Connection()
{

      string str2 = (QString(IpEdit->text())).toStdString();
     strncpy(str3, str2.c_str(), 16);
     int port = (QString(PortEdit->text())).toInt();
     ctx = modbus_new_tcp(str3, port);
     while(true)
     {
      if (ctx == NULL)
        {

            Wbox->setWindowTitle("Ошибка");
            Wbox->setDetailedText("Проверьте адрес и порт на правильность.");
            Wbox->setText("Невозможно утсановить соединение");
            Wbox->setIcon(QMessageBox::Warning);
            Wbox->show();
            forRead->stop();
            forWrite->stop();
            break;

        }
      if (modbus_connect(ctx) == -1)
        {
            Cbox->setWindowTitle("Ошибка");
            Cbox->setDetailedText("Соединение было разорвано в результате отключения контроллера.");
            Cbox->setInformativeText("Невозможно установить соединеие");
            Cbox->setIcon(QMessageBox::Critical);
            Cbox->show();
            forRead->stop();
            forWrite->stop();
            modbus_free(ctx);
            break;
        }else
            {
               Ibox->setWindowTitle(" ");
          Ibox->setIcon(QMessageBox::Information);
               Ibox->setText("Соединение установлено");
               Ibox->show();
               forRead->start(100);
               forWrite->start(100);
               break;
            }

    }
}


void Connect::Read()
{


int rc;
uint16_t tab_reg[1];
   rc = modbus_read_registers(ctx, 0,  1, tab_reg);
            if (rc == -1)
            {
               Rebox->setWindowTitle("Ошибка");
                Rebox->setText("Ошибка при чтении");
                Rebox->setDetailedText("Ошибка связи.Возможно контроллер был отключен или произошли сбои в сети. Установите соединение заново.");
                Rebox->setIcon(QMessageBox::Critical);
                forRead->stop();
                forWrite->stop();
                Rebox->show();
                PowerWent = 9999;

            }

    PowerWent = static_cast<double>(tab_reg[0]);
    if (PowerWent > MaxPower/*Kontroller*/)
        PowerWent = MaxPower/*Kontroller*/;



}

void Connect::Write()
{
    uint16_t write_reg[2]{  static_cast<uint16_t>(inShahta*(MaxPower/MaximumTemp)),
                              static_cast<uint16_t>(outside*(MaxPower/MaximumTemp))};

int rc = modbus_write_registers( ctx, 10 ,2, write_reg);
              if (rc == -1)
                {

                   Wrbox->setWindowTitle("Ошибка");
                  Wrbox->setText("Ошибка при попытке записи");
                    Wrbox->setDetailedText("Ошибка связи.Возможно контроллер был отключен или произошли сбои в сети. Установите соединение заново.");
                    Wrbox->setIcon(QMessageBox::Critical);
                    forRead->stop();
                    forWrite->stop();
                    Wrbox->show();
                    PowerWent = 9999;

                }
}
