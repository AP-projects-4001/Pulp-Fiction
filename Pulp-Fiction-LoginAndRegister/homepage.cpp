#include "homepage.h"
#include "ui_homepage.h"
#include <QListWidgetItem>
#include <QLabel>
#include "maindatabase.h"
#include "mythread.h"
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

    mythread = new MyThread(this);
    connect(mythread , SIGNAL(NumberChange()) , this , SLOT(getMessage()));

    //here i get all channels and groups and pvs and i make my list widget of chats;
    StorePv = howAmI.get_PVchatsID();
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
        pv->set_Addressee(obchat.get_Addressee());
        pv->set_ID(obchat.get_ID());
        vec.push_back(pv);
    }
    StoreGroup = howAmI.get_GroupsID();
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
        group->set_ID(obchat.get_ID());
        vec.push_back(group);
    }
    StoreChannel = howAmI.get_ChannelsID();
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
        channelOB->set_ID      (obchat.get_ID());
        channelOB->set_Owner   (obchat.get_Owner());
        vec.push_back(channelOB);
    }

    ui->listofusersgroupschanels->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    connect(ui->listofusersgroupschanels, SIGNAL(itemClicked(QListWidgetItem*)),
                this, SLOT(clicked_list_item(QListWidgetItem*)));
    connect(ui->Sendbtn, &QPushButton::clicked,
         this, &homepage::send_clicked);
    mythread->start();
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
            Group* ptr1 = dynamic_cast<Group*>(ptr);

            if(ptr1 != nullptr)
            {
                currentMode = GroupMode;
                Display(true);
                return;
            }
            channel* ptr2 = dynamic_cast<channel*>(ptr);
            if(ptr2 != nullptr)
            {
                currentMode = ChannnelMode;
                Display(isAdmin(howAmI));
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
        ui->infobtn->setText(c_str2);
        ui->infobtn->show();
        ui->messagelineedit->setFocus(Qt::OtherFocusReason);
    }
    vectroToList();

}
void homepage::send_clicked()
{
    QString mes = ui->messagelineedit->toPlainText();
    qDebug() << mes;
    if(!(mes.isEmpty()))
    {
       mes =  howAmI.get_UserName() + ":\n" + mes;
       QString dir =  vec[index]->ExtractFileName(vec[index]->get_ID());
       vec[index]->add_Message(mes , dir ) ;
       auto item = new QListWidgetItem("", ui->messageslist);
       auto text = new QLabel;
       QByteArray ba = mes.toLocal8Bit();
       const char *c_str2 = ba.data();
       text->setText(c_str2);
       text->setStyleSheet("QLabel { background-color : rgba(255,180,0,100%); color : black; }");
       text->setMinimumSize(200, 40);
       text->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
       text->setWordWrap(true);
       layout->addWidget(text);
       ui->messageslist->setItemWidget(item, text);
       ui->messagelineedit->clear();
       ui->messagelineedit->setFocus(Qt::OtherFocusReason);
    }

}

void homepage::vectroToList()
{
    QVector<QString> write;
    if(vec.empty())
        return;
    if(currentMode==PvMode)
    {
        pvchat obchat = pvchat::read_PVChat(vec[index]->get_ID());
        write = obchat.get_Messages();
    }
    else if(currentMode == GroupMode)
    {
        Group obchat = Group::read_Group(vec[index]->get_ID());
        write = obchat.get_Messages();
    }
    else if(currentMode == ChannnelMode)
    {
        channel obchat = channel::read_channel(vec[index]->get_ID());
        write = obchat.get_Messages();
    }

    ui->messageslist->show();
    ui->messageslist->setStyleSheet("background-color : rgba(255,0,0,0%); color : white;");
    ui->messageslist->setFlow(QListView::LeftToRight);
    ui->messageslist->setGridSize(QSize(400, 50));
    ui->messageslist->setResizeMode(QListView::Adjust);
    ui->messageslist->setViewMode(QListView::ListMode);
    ui->messageslist->setWrapping(true);
    layout = new QVBoxLayout;
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
        text->setStyleSheet("QLabel { background-color : rgba(255, 180,0,100%); color : black; }");
        text->setMinimumSize(200, 40);
        text->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        text->setWordWrap(true);
        layout->addWidget(text);

        ui->messageslist->setItemWidget(item, text);
    }
}

void homepage::on_actionNew_group_triggered()
{
    dialog = new createchannel(howAmI);
    dialog->show();
    if(dialog->exec() == QDialog::Accepted)
    {
        int j = maindatabase::Creat_GroupID();
        QByteArray ba1 = dialog->getName().toLocal8Bit();
        const char *c_str21 = ba1.data();
        Group gr(howAmI , c_str21);
        gr.set_ID(j);
        gr.Make_NewGroupFile(gr.ExtractFileName(j));
        maindatabase::Add_Group(gr);
        gr.add_Member(howAmI , gr.ExtractFileName(j));
        maindatabase::Push_UserGroupID(j,howAmI);
        for(int i = 0 ; i < dialog->getCount() ; i++)
        {
            if(dialog->cheVec[i]->isChecked())
            {
                gr.add_Member(dialog->selected[i] , gr.ExtractFileName(j));
                maindatabase::Push_UserGroupID(j,dialog->selected[i]);
            }

        }
        Group obchat = Group::read_Group(j);
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
        StoreGroup.push_back(obchat.get_ID());
        vec.push_back(group);
        clicked_list_item(item);
    }
}


void homepage::on_newgroupbtn_clicked()
{
    creategroupdialog = new creategroup(howAmI, this);
    creategroupdialog->show();
    if(creategroupdialog->exec() == QDialog::Accepted)
    {
        int j = maindatabase::Creat_GroupID();
        QByteArray ba1 = dialog->getName().toLocal8Bit();
        const char *c_str21 = ba1.data();
        Group gr(howAmI , c_str21);
        gr.set_ID(j);
        gr.Make_NewGroupFile(gr.ExtractFileName(j));
        maindatabase::Add_Group(gr);
        maindatabase::Push_UserGroupID(j,howAmI);
        gr.add_Member(howAmI , gr.ExtractFileName(j));
        for(int i = 0 ; i < dialog->getCount() ; i++)
        {
            if(dialog->cheVec[i]->isChecked())
            {
                gr.add_Member(dialog->selected[i] , gr.ExtractFileName(j));
                maindatabase::Push_UserGroupID(j,dialog->selected[i]);
            }

        }
        Group obchat = Group::read_Group(j);
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
        group->set_ID(obchat.get_ID());
        StoreGroup.push_back(obchat.get_ID());
        vec.push_back(group);
        clicked_list_item(item);
    }
}


void homepage::on_newchannelbtn_clicked()
{
    dialog = new createchannel(howAmI, this);
    dialog->show();
    if(dialog->exec() == QDialog::Accepted)
    {
        int j = maindatabase::Creat_ChannelID();
        QByteArray ba1 = dialog->getName().toLocal8Bit();
        const char *c_str21 = ba1.data();
        channel gr(howAmI , c_str21);
        gr.set_ID(j);
        gr.Make_NewChannelFile(gr.ExtractFileName(j));
        maindatabase::Add_Channel(gr);
        gr.add_Admins(howAmI , gr.ExtractFileName(j));
        maindatabase::Push_UserChannelID(j,howAmI);
        for(int i = 0 ; i < dialog->getCount() ; i++)
        {
            if(dialog->cheVec[i]->isChecked())
            {
                gr.add_Member(dialog->selected[i] , gr.ExtractFileName(j));
                maindatabase::Push_UserChannelID(j,dialog->selected[i]);
            }

        }
        /** pay attention**/
        channel obchat = channel::read_channel(j);
        QString s = obchat.get_ChannelName();
        QByteArray ba = s.toLocal8Bit();
        const char *c_str2 = ba.data();
        QListWidgetItem* item = new QListWidgetItem;
        item->setText(c_str2);
        item->setForeground(Qt::white);
        ui->listofusersgroupschanels->addItem(item);
        list.push_back(item);
        channelOB = new channel (obchat.get_Owner() , obchat.get_ChannelName());
        channelOB->setName    (obchat.get_ChannelName());
        channelOB->set_Members(obchat.get_Members());
        channelOB->set_Admins (obchat.get_Admins());
        channelOB->set_Messages(obchat.get_Messages());
        channelOB->set_ID(obchat.get_ID());
        StoreChannel.push_back(obchat.get_ID());
        vec.push_back(channelOB);
        clicked_list_item(item);
    }
}


void homepage::on_infobtn_clicked()
{
    if(currentMode == GroupMode)
    {
        Group obchat = Group::read_Group(vec[index]->get_ID());
        infoGroup = new groupInfo(howAmI , obchat.get_Member() , obchat.get_ID());
        infoGroup->setStyleSheet("QWidget{\
                                     background-color: white\
                                     }");
        infoGroup->show();

    }
    if(currentMode == ChannnelMode)
    {
        channel obchat = channel::read_channel(vec[index]->get_ID());
        qDebug() << obchat.get_ID();
        infoChannel = new channelInfo(howAmI , obchat.get_Members() ,obchat.get_Admins(), obchat.get_ID());
        infoChannel->setStyleSheet("QWidget{\
                                     background-color: white\
                                     }");
        infoChannel->show();
    }
    if(currentMode == PvMode)
    {
            pvchat obchat = pvchat::read_PVChat(vec[index]->get_ID());
            qDebug() << obchat.get_ID();
            infoPv = new PvInfo(howAmI , obchat.get_Addressee());
            infoPv->setStyleSheet("QWidget{\
                                         background-color: white\
                                         }");
            infoPv->show();
    }
}
/** this function **/
void homepage::whatIsNew()
{
    maindatabase::Find_user(howAmI);
    QVector<int> TemChannel = howAmI.get_ChannelsID();
    int i1 = TemChannel.size();
    int j1 = StoreChannel.size();
    if(i1 > j1)
    {
        for(int it1 = j1 ; it1 != i1 ; it1++ )
        {
            channel obchat = channel::read_channel(TemChannel[it1]);
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
            channelOB->set_ID      (obchat.get_ID());
            channelOB->set_Owner   (obchat.get_Owner());
            vec.push_back(channelOB);
            StoreChannel.push_back(TemChannel[it1]);
        }
    }

    QVector<int> TemGroup = howAmI.get_GroupsID();
    int i = TemGroup.size();
    int j = StoreGroup.size();
    if(i > j)
    {
       for(int it = j ; it != i ; it++ )
       {
            Group obchat = Group::read_Group(TemGroup[it]);
            QString s = obchat.get_GroupName();
            QByteArray ba = s.toLocal8Bit();
            const char *c_str2 = ba.data();
            QListWidgetItem* item = new QListWidgetItem;
            item->setText(c_str2);
            item->setForeground(Qt::white);
            ui->listofusersgroupschanels->addItem(item);
            list.push_back(item);
            group = new Group(obchat.get_Owner() , obchat.get_GroupName());
            group->setName     (obchat.get_GroupName());
            group->set_Messages(obchat.get_Messages());
            group->set_Members (obchat.get_Member());
            group->set_ID      (obchat.get_ID());
            group->set_Owner   (obchat.get_Owner());
            vec.push_back(group);
            StoreGroup.push_back(obchat.get_ID());
        }
    }
    QVector<int> TemPv = howAmI.get_PVchatsID();
    int i2 = TemPv.size();
    int j2 = StorePv.size();
    if(i2 > j2)
    {
        for(int it2 = j2 ; it2 != i2 ; it2++ )
        {
            pvchat obchat = pvchat::read_PVChat(TemPv[it2]);
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
            pv->set_Addressee(obchat.get_Addressee());
            pv->set_ID(obchat.get_ID());
            vec.push_back(pv);
            StorePv.push_back(TemPv[it2]);
        }
    }
}
void homepage::getMessage()
{
    vectroToList();
    whatIsNew();
}
bool homepage::isAdmin(user me)
{
    channel obchat = channel::read_channel(vec[index]->get_ID());
    QVector<user> Ad = obchat.get_Admins();
    QVector<user>::iterator it;
    for(it = Ad.begin() ; it != Ad.end() ; it++)
    {
        if (it->get_ID() == me.get_ID())
            return true;
    }
    return false;
}

void homepage::on_contactsbtn_clicked()
{
    contactDialog = new Contacts(howAmI, this);
    contactDialog->show();
}
void homepage::on_settingbtn_clicked()
{
    settingDialog = new Setting(howAmI, this);
    settingDialog->show();
}
void homepage::on_actionSetting_triggered()
{
    on_settingbtn_clicked();
}

void homepage::on_actionContacts_triggered()
{
    on_contactsbtn_clicked();
}


void homepage::on_actionExit_triggered()
{
    QApplication::quit();
}

/** this function **/
void homepage::on_actionNew_channel_triggered()
{
    dialog = new createchannel(howAmI);
    dialog->show();
    if(dialog->exec() == QDialog::Accepted)
    {
        int j = maindatabase::Creat_ChannelID();
        QByteArray ba1 = dialog->getName().toLocal8Bit();
        const char *c_str21 = ba1.data();
        channel gr(howAmI , c_str21);
        gr.set_ID(j);
        gr.Make_NewChannelFile(gr.ExtractFileName(j));
        maindatabase::Add_Channel(gr);
        gr.add_Admins(howAmI , gr.ExtractFileName(j));
        maindatabase::Push_UserChannelID(j,howAmI);
        for(int i = 0 ; i < dialog->getCount() ; i++)
        {
            if(dialog->cheVec[i]->isChecked())
            {
                gr.add_Member(dialog->selected[i] , gr.ExtractFileName(j));
                maindatabase::Push_UserChannelID(j,dialog->selected[i]);
            }

        }
        channel obchat = channel::read_channel(j);
        QString s = obchat.get_ChannelName();
        qDebug() << s;
        QByteArray ba = s.toLocal8Bit();
        const char *c_str2 = ba.data();
        QListWidgetItem* item = new QListWidgetItem;
        item->setText(c_str2);
        item->setForeground(Qt::white);
        ui->listofusersgroupschanels->addItem(item);
        list.push_back(item);
        channelOB = new channel (obchat.get_Owner() , obchat.get_ChannelName());
        channelOB->setName    (obchat.get_ChannelName());
        channelOB->set_Members(obchat.get_Members());
        channelOB->set_Admins (obchat.get_Admins());
        channelOB->set_Messages(obchat.get_Messages());
        channelOB->set_ID(obchat.get_ID());
        StoreChannel.push_back(obchat.get_ID());
        vec.push_back(channelOB);
        clicked_list_item(item);
    }
}

