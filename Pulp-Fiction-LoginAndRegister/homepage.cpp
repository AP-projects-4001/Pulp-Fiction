#include "homepage.h"
#include "ui_homepage.h"
#include <QListWidgetItem>
#include <QLabel>
#include "maindatabase.h"
QVector<chat*> vec;
homepage::homepage(user me ,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::homepage)
{
    ui->setupUi(this);
    howAmI = me;
    ui->messagelineedit->hide();
    ui->infobtn->hide();
    ui->Sendbtn->hide();
    ui->messageslist->hide();


    QListWidgetItem* item = new QListWidgetItem;
    QListWidgetItem* item1 = new QListWidgetItem;
    QListWidgetItem* item2 = new QListWidgetItem;
    item->setIcon(QIcon(":/img/img/icons8-people-40.png"));
    item1->setIcon(QIcon(":/img/img/icons8-contacts-40.png"));
    item2->setIcon(QIcon(":/img/img/icons8-setting-40.png"));
    ui->sidebar->addItem(item);
    ui->sidebar->addItem(item1);
    ui->sidebar->addItem(item2);

    //here i get all channels and chats and pvs and i make my list widget of chats;
    QVector<int> StorePv = howAmI.get_PVchatsID();
    QVector<int>::Iterator pvid;
    for(pvid = StorePv.begin() ; pvid != StorePv.end() ; pvid++)
    {

        pvchat obchat = pvchat::read_PVChat(*pvid);
        user me = obchat.get_Owner();
        user you = obchat.get_Addressee();
        QString s = obchat.get_Addressee().get_UserName();
        QByteArray ba = s.toLocal8Bit();
        const char *c_str2 = ba.data();
        QListWidgetItem* item = new QListWidgetItem;
        item->setText(c_str2);
        item->setForeground(Qt::white);
        ui->listofusersgroupschanels->addItem(item);
        list.push_back(item);
        pv = new pvchat(me , you);
        pv->setName(obchat.get_Addressee().get_UserName());
        pv->set_Messages(obchat.get_Messages());
        vec.push_back(pv);
    }
    QVector<int> StoreGroup = howAmI.get_GroupsID();
    qDebug() << "kfkfkfkfkkfkfk " << StoreGroup;
    QVector<int>::Iterator grid;
    for(grid = StoreGroup.begin() ; grid != StoreGroup.end() ; grid++)
    {
        Group obchat = Group::read_Group(*grid);
        QString s = obchat.get_GroupName();
        QByteArray ba = s.toLocal8Bit();
        const char *c_str2 = ba.data();
        QListWidgetItem* item = new QListWidgetItem;
        item->setText(c_str2);
        item->setForeground(Qt::white);
        ui->listofusersgroupschanels->addItem(item);
        list.push_back(item);
        group = new Group (obchat.get_Owner() , obchat.get_GroupName());
        group->setName    (obchat.get_GroupName());
        group->set_Members(obchat.get_Member());
        group->set_Messages(obchat.get_Messages());
        vec.push_back(group);
    }

    QVector<int> StoreChannel = howAmI.get_ChannelsID();
    qDebug() << "kfkfkfkfkkfkfk " << howAmI.get_ChannelsID();
    QVector<int>::Iterator chid;
    for(chid = StoreChannel.begin() ; chid != StoreChannel.end() ; chid++)
    {
        channel obchat = channel::read_channel(*chid);
        //qDebug() << obchat.
        QString s = obchat.get_ChannelName();
        QByteArray ba = s.toLocal8Bit();
        const char *c_str2 = ba.data();
        QListWidgetItem* item = new QListWidgetItem;
        item->setText(c_str2);
        item->setForeground(Qt::white);
        ui->listofusersgroupschanels->addItem(item);
        list.push_back(item);
        channelOB = new channel(obchat.get_Owner() , obchat.get_ChannelName());
        channelOB->setName     (obchat.get_ChannelName());
        channelOB->set_Messages(obchat.get_Messages());
        channelOB->set_Admins  (obchat.get_Admins());
        channelOB->set_Members (obchat.get_Members());
        channelOB->set_Messages(obchat.get_Messages());
        vec.push_back(channelOB);
    }

    ui->listofusersgroupschanels->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    connect(ui->listofusersgroupschanels, SIGNAL(itemClicked(QListWidgetItem*)),
                this, SLOT(clicked_list_item(QListWidgetItem*)));
    connect(ui->sidebar, SIGNAL(slidebarClicked(QListWidgetItem*)),
                this, SLOT(slidebar_clicked(QListWidgetItem*)));
    connect(ui->Sendbtn, &QPushButton::clicked,
         this, &homepage::send_clicked);
    connect(ui->infobtn, &QPushButton::clicked,
         this, &homepage::info_clicked);

//    connect(ui->listofusersgroupschanels, SIGNAL(itemClicked(QListWidgetItem*)),
//                this, SLOT(clicked_list_item(QListWidgetItem*)));
//    connect(ui->Sendbtn, &QPushButton::clicked,
//                  this, &homepage::on_Sendbtn_clicked);
//    connect(ui->infobtn, &QPushButton::clicked,
//                    this, &Ui_homepage::infobtn);

}



homepage::~homepage()
{
    delete ui;
}
void homepage::clicked_list_item(QListWidgetItem* item)
{
    //multi
    //thread t1(returnmes)
    //thread t2(send_clicked)
    for(int i = 0; i < ui->listofusersgroupschanels->count(); ++i)
    {
        if(ui->listofusersgroupschanels->item(i) == item)
        {
            index=i;
            ptr = vec[i];
            qDebug() << ptr->get_Messages();

            Group* ptr1 = dynamic_cast<Group*>(ptr);

            if(ptr1 != nullptr)
            {
                currentMode = ChatMode;
                Display(true);
                return;
            }
            channel* ptr2 = dynamic_cast<channel*>(ptr);
            if(ptr2 != nullptr)
            {
                currentMode = ChannnelMode;
                Display(ptr2->isAdminfunction());
                return;
            }
            pvchat* ptr3 = dynamic_cast<pvchat*>(ptr);
            if(ptr3 != nullptr)
            {
                currentMode = PvMode;
                Display(true);
                return;
            }

        }
    }
}
void homepage::slidebar_clicked(QListWidgetItem* item)
{
    dialog->show();
    for(int i = 0; i < ui->sidebar->count(); ++i)
    {

        //if(i==0)

    }
}
void homepage::Display(bool isAd)
{
    ui->messagelineedit->hide();
    ui->Sendbtn->hide();
    ui->infobtn->hide();
    ui->messageslist->show();
    ui->messagelineedit->clear();
    if(isAd)
    {
        ui->messagelineedit->show();
        ui->Sendbtn->show();
        QString name = vec[index]->getName();
        QByteArray ba = name.toLocal8Bit();
        const char *c_str2 = ba.data();
        qDebug() << name;
        ui->infobtn->setText(c_str2);
        ui->infobtn->show();
    }
    vectroToList(vec[index]->get_Messages());
}
void homepage::send_clicked()
{
    QString mes = ui->messagelineedit->text();
    if(!(mes.isEmpty()))
    {
       QString dir =  vec[index]->ExtractFileName(vec[index]->get_ID());/**save id each class to ID chat1;**/
       vec[index]->add_Message(mes , dir ) ;
    }

}
void homepage::info_clicked()
{
   dialog = new newGroup(howAmI);
   dialog->show();
   for(int i = 0 ; i < dialog->getCount() ; i++)
   {
       if(dialog->cheVec[i]->isChecked())
       {

           int i = maindatabase::Creat_GroupID();
           Group g(howAmI , "popoppopopopo");
           g.Make_NewGroupFile(g.ExtractFileName(i));
           //g.add_Member(u,g.get_GroupName());
           maindatabase::Add_Group(g);
           //maindatabase::Push_UserGroupID(i,u);
           maindatabase::Push_UserGroupID(i,howAmI);
           g.add_Message("hghghghg" , g.ExtractFileName(i));
           g.add_Message("dkkdkkd" , g.ExtractFileName(i));

           Group obchat = Group::read_Group(i);
           QString s = obchat.get_GroupName();
           QByteArray ba = s.toLocal8Bit();
           const char *c_str2 = ba.data();
           QListWidgetItem* item = new QListWidgetItem;
           item->setText(c_str2);
           item->setForeground(Qt::white);
           ui->listofusersgroupschanels->addItem(item);
           list.push_back(item);
           group = new Group (obchat.get_Owner() , obchat.get_GroupName());
           group->setName    (obchat.get_GroupName());
           group->set_Members(obchat.get_Member());
           group->set_Messages(obchat.get_Messages());
           vec.push_back(group);
       }
   }

   /* if(currentMode != PvMode)
    {
         channel_and_chat_dialog* obDialog= new channel_and_chat_dialog(vec[index]);
         obDialog->setStyleSheet("QWidget{\
                                 background-color: black\
                                 }");
         obDialog->show();
    }*/
}
void homepage::vectroToList(QVector<QString> write)
{

    ui->messageslist->show();
    ui->messageslist->setStyleSheet("background-color : rgba(255,0,0,0%); color : white;");
    ui->messageslist->setFlow(QListView::LeftToRight);
    ui->messageslist->setGridSize(QSize(400, 50));
    ui->messageslist->setResizeMode(QListView::Adjust);
    ui->messageslist->setViewMode(QListView::ListMode);
    ui->messageslist->setWrapping(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSizeConstraint(QLayout::SetMinimumSize);
    this->setLayout(layout);
    ui->messageslist->clear();

    QVector<QString>::iterator itt;
    for (itt = write.begin(); itt != write.end(); ++itt) {
        auto item = new QListWidgetItem("", ui->messageslist);
        auto text = new QLabel;
        QByteArray ba = (*itt).toLocal8Bit();
        const char *c_str2 = ba.data();
        text->setText(c_str2);
        text->setStyleSheet("QLabel { background-color : rgba(0,0,0,10%); color : black; }");
        text->setMinimumSize(200, 40);
        text->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        text->setWordWrap(true);
        layout->addWidget(text);

        ui->messageslist->setItemWidget(item, text);
    }
}

//void homepage::on_actionExit_triggered()
//{
//    QApplication::quit();
//}



//void homepage::on_listofusersgroupschanels_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
//{

//}




