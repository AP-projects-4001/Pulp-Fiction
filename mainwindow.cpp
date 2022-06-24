#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "baseclass.h"
#include "channelclass.h"
#include "groupclass.h"
#include "pvclass.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->messageLine->hide();
    ui->infoButton->hide();
    ui->messageEdit->hide();
    ui->sendButton->hide();
    ui->name->hide();



    QVector<QString> vecme = {"arash","negar"};
    QVector<QString> vecMes = {"hello","bye" , "group"};
    QVector<int> vint= {1,2,3};
    QVector<int> vin= {1,2,3};
    int i = 4;
    QString s ="iut";
    QString n = "arefe";
    QVector<QString> vecAd = {"fhf","fjjf"};
    ob1 = new groupClass(i,n,s,6,vin,vecme,vint,vecAd , vecMes );
    vec.push_back(ob1);

    QVector<QString> vecme1 = {"arash","negar"};
    QVector<QString> vecMes1 = {"hello","bye" , "channel"};
    QVector<int> vint1= {1,2,3};
    QVector<int> vin1= {1,2,3};
    int i1 = 4;
    QString s1 ="iut";
    QVector<QString> vecAd1 = {"fhf","fjjf"};
    ob = new channelClass(i1,s1,6,vin1,vecme1,vint1,vecAd1 , vecMes1 );
    vec.push_back(ob);

    QVector<QString> vecMes2 = {"hello","bye" , "pv"};
    int i2 = 4;
    QString s2 ="iut";
    ob2 = new pvClass(i2,6, s2 , vecMes2);
    vec.push_back(ob2);

    ui->chatList->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    for(int a = 0 ; a < 3 ; a++)
    {
        QListWidgetItem* item = new QListWidgetItem;
        item->setText(QString::number(a));
        item->setForeground(Qt::white);
        chat.push_back(item);
        ui->chatList->addItem(item);
    }

    connect(ui->chatList, SIGNAL(itemClicked(QListWidgetItem*)),
                this, SLOT(clicked_list_item(QListWidgetItem*)));
    connect(ui->sendButton, &QPushButton::clicked,
         this, &MainWindow::send_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clicked_list_item(QListWidgetItem* item)
{
    for(int i = 0; i < ui->chatList->count(); ++i)
    {
        if(ui->chatList->item(i) == item)
        {
            baseClass* ptr = vec[i];
            index = i;
            ui->messageEdit->clear();
            vectroToList(ptr->getMessages() , ui->messageEdit);
            groupClass* ptr1 = dynamic_cast<groupClass*>(ptr);
            if(ptr1 != nullptr)
            {

                Display(true);
                return;
            }
            channelClass* ptr2 = dynamic_cast<channelClass*>(ptr);
            if(ptr2 != nullptr)
            {

                Display(ptr2->getAdmin());
                return;
            }
            pvClass* ptr3 = dynamic_cast<pvClass*>(ptr);
            if(ptr3 != nullptr)
            {

                Display(true);
                return;
            }

        }
    }
}

void MainWindow::Display(bool isAd)
{
    ui->messageLine->hide();
    ui->sendButton->hide();
    ui->infoButton->hide();
    ui->messageEdit->show();
    ui->messageLine->clear();
    ui->messageEdit->setReadOnly(true);
    ui->name->show();
    if(isAd)
    {
        ui->messageLine->show();
        ui->sendButton->show();
        ui->infoButton->show();
    }
}
void MainWindow::send_clicked()
{
    QString mes = ui->messageLine->text();
    if(!(mes.isEmpty()))
    {
    ui->messageEdit->append(mes);
    ui->messageLine->clear();
    ui->messageLine->setFocus(Qt::OtherFocusReason);
    }

}
