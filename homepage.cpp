#include "homepage.h"
#include "ui_homepage.h"
#include <QListWidgetItem>
#include <QLabel>

homepage::homepage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::homepage)
{
    ui->setupUi(this);

//    ui->messagelineedit->hide();
//    ui->infobtn->hide();
//    ui->Sendbtn->hide();
//    ui->listofusersgroupschanels->hide();




    QListWidgetItem* item = new QListWidgetItem;
    QListWidgetItem* item1 = new QListWidgetItem;
    QListWidgetItem* item2 = new QListWidgetItem;
    item->setIcon(QIcon(":/img/img/icons8-people-40.png"));
    item1->setIcon(QIcon(":/img/img/icons8-contacts-40.png"));
    item2->setIcon(QIcon(":/img/img/icons8-setting-40.png"));
    ui->sidebar->addItem(item);
    ui->sidebar->addItem(item1);
    ui->sidebar->addItem(item2);

//    QVector<QString> vecme = {"arash","negar"};
//    QVector<QString> vecMes = {"hello","bye" , "group"};
//    QVector<int> vint= {1,2,3};
//    QVector<int> vin= {1,2,3};
//    int i = 4;
//    QString s ="iut";
//    QString n = "arefe";
//    QVector<QString> vecAd = {"fhf","fjjf"};
//    group = new groupClass(i,n,s,6,vin,vecme,vint,vecAd , vecMes );
//    vec.push_back(group);

//    QVector<QString> vecme1 = {"arash","negar"};
//    QVector<QString> vecMes1 = {"hello","bye" , "channel"};
//    QVector<int> vint1= {1,2,3};
//    QVector<int> vin1= {1,2,3};
//    int i1 = 4;
//    QString s1 ="iut";
//    QVector<QString> vecAd1 = {"fhf","fjjf"};
//    chanel = new channelClass(i1,s1,6,vin1,vecme1,vint1,vecAd1 , vecMes1 );
//    vec.push_back(chanel);

//    QVector<QString> vecMes2 = {"hello","bye" , "pv"};
//    int i2 = 4;
//    QString s2 ="iut";
//    pv = new pvClass(i2,6, s2 , vecMes2);
//    vec.push_back(pv);

//    ui->listofusersgroupschanels->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);


//    for(int a = 0 ; a < 3 ; a++)
//    {
//        QListWidgetItem* item = new QListWidgetItem;
//        item->setText(QString::number(a));
//        item->setForeground(Qt::white);
//        chat.push_back(item);
//        ui->listofusersgroupschanels->addItem(item);
//    }

//    connect(ui->listofusersgroupschanels, SIGNAL(itemClicked(QListWidgetItem*)),
//                this, SLOT(clicked_list_item(QListWidgetItem*)));
//    connect(ui->Sendbtn, &QPushButton::clicked,
//         this, &homepage::on_Sendbtn_clicked);
//    connect(ui->infobtn, &QPushButton::clicked,
    //         this, &Ui_homepage::infobtn);
}

//void homepage::vectroToList(QVector<QString> write)
//{
//    /*QLabel *label =  new QLabel();
//    label->setText("This is how i add a label");
//    label->setMinimumWidth(100);
//    ui->verticalLayout->addWidget(label);*/
//    ui->messageslist->show();
//    ui->messageslist->setStyleSheet("background-color : rgba(255,0,0,0%); color : white;");
//    ui->messageslist->setFlow(QListView::LeftToRight);
//    ui->messageslist->setGridSize(QSize(300, 90));
//    ui->messageslist->setResizeMode(QListView::Adjust);
//    ui->messageslist->setViewMode(QListView::ListMode);
//    ui->messageslist->setWrapping(true);

//    QVBoxLayout *layout = new QVBoxLayout;
//    layout->setSizeConstraint(QLayout::SetMinimumSize);
//    this->setLayout(layout);
//    ui->messageslist->clear();
//    for (int i = 0 ; i < 5 ; i ++) {
//        auto    item = new QListWidgetItem("", ui->messageslist);
//        auto    text = new QLabel("content is kddddddddddddddddddddddddd dkkkkkkkkkkkkkkkkkkkkkkkk kdddddddddd  kfkkkkkkkkkkkkkkkk kdkdkdkdk kdkkdkdkdk ");
//        text->setStyleSheet("QLabel { background-color : black; color : white; }");
//        text->setMinimumSize(200, 80);
//        text->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
//        text->setWordWrap(true);
//        layout->addWidget(text);


//        ui->messageslist->setItemWidget(item, text);
//    }

//    /*QVector<QString>::iterator itt;
//    for (itt = write.begin(); itt != write.end(); ++itt)
//    {
//        read->append(*itt);
//    }*/

//}

homepage::~homepage()
{
    delete ui;
}

void homepage::on_actionExit_triggered()
{
    QApplication::quit();
}


//void homepage::on_Sendbtn_clicked()
//{
//    QString mes = ui->messagelineedit->text();
//    if(!(mes.isEmpty()))
//    {
//        ui->listofusersgroupschanels->addItem(mes);
//    //ui->textEdit->append(mes);
//    //ui->textEdit->clear();
//    //ui->textEdit->setFocus(Qt::OtherFocusReason);
//    }
//}


//void homepage::on_listofusersgroupschanels_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
//{

//}


//void homepage::on_listofusersgroupschanels_itemClicked(QListWidgetItem *item)
//{
//    //multi
//    //thread t1(returnmes)
//    //thread t2(send_clicked)
//    for(int i = 0; i < ui->listofusersgroupschanels->count(); ++i)
//    {
//        if(ui->listofusersgroupschanels->item(i) == item)
//        {
//            baseClass* ptr = vec[i];
//            index = i;
//            //ui->messageEdit->clear();
//            vectroToList(ptr->getMessages());
//            groupClass* ptr1 = dynamic_cast<groupClass*>(ptr);
//            if(ptr1 != nullptr)
//            {
//                currentMode = ChatMode;
//                Display(true);
//                return;
//            }
//            channelClass* ptr2 = dynamic_cast<channelClass*>(ptr);
//            if(ptr2 != nullptr)
//            {
//                currentMode = ChannnelMode;
//                Display(ptr2->getAdmin());
//                return;
//            }
//            pvClass* ptr3 = dynamic_cast<pvClass*>(ptr);
//            if(ptr3 != nullptr)
//            {
//                currentMode = PvMode;
//                Display(true);
//                return;
//            }

//        }
//    }
//}

//void homepage::Display(bool isAd)
//{
//    ui->messagelineedit->hide();
//    ui->Sendbtn->hide();
//    ui->Sendbtn->hide();
//    //ui->textEdit->show();
//    ui->messagelineedit->clear();
//    //ui->textEdit->setReadOnly(true);
//    //ui->textEdit->setStyleSheet("background-color : rgba(255,0,0,10%); color : white;");
//    //ui->name->show();
//    if(isAd)
//    {
//        ui->messagelineedit->show();
//        ui->Sendbtn->show();
//        ui->infobtn->show();
//    }
//
