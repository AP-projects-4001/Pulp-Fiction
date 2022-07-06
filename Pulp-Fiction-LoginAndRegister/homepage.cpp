#include "homepage.h"
#include "countlessCalledFunctions.h"
#include "ui_homepage.h"
#include <QListWidgetItem>
#include <QLabel>
#include "maindatabase.h"
#include "mythread.h"
#include <QScrollBar>

homepage::homepage(user me ,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::homepage)
{
    ui->setupUi(this);


    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(20.0);
    bodyShadow->setDistance(4.0);
    bodyShadow->setColor(QColor(10, 5, 45, 80));
    ui->widget->setGraphicsEffect(bodyShadow);



    howAmI = me;
    ui->messagelineedit->hide();
    ui->infobtn->hide();
    ui->Sendbtn->hide();
    ui->messageslist->hide();
    ui->widget_2->hide();


    //here i get all channels , groups and pvs and i make a list widget of chats;
    StorePv = howAmI.get_PVchatsID();

    QVector<int>::Iterator pvid;
    for(pvid = StorePv.begin() ; pvid != StorePv.end() ; pvid++)
    {
        pvchat obchat = pvchat::read_PVChat(*pvid);
        QString s;
        if(obchat.get_Addressee().get_ID() == howAmI.get_ID())
        {
            s = obchat.get_Owner().get_UserName();
            PVs.push_back(obchat.get_Owner());
        }
        else
        {
            s = obchat.get_Addressee().get_UserName();
            PVs.push_back(obchat.get_Addressee());
        }

        QListWidgetItem *item = setItemsInListWIdget(ui->listofusersgroupschanels , s);
        list.push_back(item);

        pv = new pvchat(obchat , howAmI);
        vec.push_back(pv);

    }

    StoreGroup = howAmI.get_GroupsID();

    QVector<int>::Iterator grid;
    for(grid = StoreGroup.begin() ; grid != StoreGroup.end() ; grid++)
    {
        Group obchat = Group::read_Group(*grid);
        QString s = obchat.get_GroupName();

        QListWidgetItem *item = setItemsInListWIdget(ui->listofusersgroupschanels , s);
        list.push_back(item);

        group = new Group  (obchat);
        vec.push_back(group);
    }

    StoreChannel = howAmI.get_ChannelsID();

    QVector<int>::Iterator chid;
    for(chid = StoreChannel.begin() ; chid != StoreChannel.end() ; chid++)
    {
        channel obchat = channel::read_channel(*chid);
        QString s = obchat.get_ChannelName();

        QListWidgetItem *item = setItemsInListWIdget(ui->listofusersgroupschanels , s);
        list.push_back(item);

        channelOB = new channel(obchat);
        vec.push_back(channelOB);
    }

    ui->listofusersgroupschanels->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    ui->messageslist->setStyleSheet("QListWidget#messageslist "
                                    "{border-image: url(:/img/img/chatbackground.jpg);color: white;border-radius: 10px;background-color: rgb(42, 46, 52);"
                                    "padding-left: 10px;padding-top: 10px; "
                                    "border-style: solid;border-color: rgb(53, 159, 159);border-width: 1px;}"
                                    "QListWidget#messageslist:hover{background-color: rgb(42, 46, 52);"
                                    "border-style: solid;border-color: rgb(53, 159, 159)}");

/////// Try to add style sheet for scrollbar ////////
//    QString css_string = "QScrollBar:vertical {"
//            "border: 2px solid grey;"
//            "background-color: rgb(42, 46, 52);border-radius: 20px;"
//            "width: 15px; padding-right: 10px"
//            "margin: 22px 0 22px 0;}"
//        "QScrollBar::handle:vertical {"
//            "background: white;"
//            "min-height: 20px;}"
//        "QScrollBar::add-line:vertical {"
//            "border: 2px solid grey;"
//            "background: #32CC99;"
//            "height: 20px;"
//            "subcontrol-position: bottom;"
//            "subcontrol-origin: margin;}"

//        "QScrollBar::sub-line:vertical {"
//            "border: 2px solid grey;border-radius: 10px;"
//            "background: #32CC99;"
//            "height: 20px;"
//            "subcontrol-position: top;"
//            "subcontrol-origin: margin;}"
//        "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"
//            "border: 2px solid grey;"
//            "width: 3px;"
//            "height: 3px;"
//            "background: white;}"

//        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
//            "background: none;}";

//    QScrollBar *vbar = ui->messageslist->verticalScrollBar();
//    vbar->setStyleSheet(css_string);


    layout = setQwidgetItemsInListWidget( ui->messageslist , 600 , 70);
    this->setLayout(layout);

    mythread = new MyThread(this);
    connect(mythread , SIGNAL(NumberChange()) , this , SLOT(getMessage()));

    connect(ui->listofusersgroupschanels, SIGNAL(itemClicked(QListWidgetItem*)),
                this, SLOT(clicked_list_item(QListWidgetItem*)));

    mythread->start();
}



homepage::~homepage()
{
    delete ui;
}
void homepage::clicked_list_item(QListWidgetItem* item)
{
    checkThread = 2;
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
    if(checkThread == 2)
    {
        ui->widget_2->show();
        ui->infobtn->hide();
        ui->Sendbtn->hide();
        ui->messagelineedit->hide();
        ui->messageslist->show();
        ui->loadingpic->hide();

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

}

void homepage::on_Sendbtn_clicked()
{
    QString mes = ui->messagelineedit->toPlainText();
    if(!(mes.isEmpty()))
    {
       mes =  howAmI.get_UserName() + ":\n" + mes;

       QString dir =  vec[index]->ExtractFileName(vec[index]->get_ID());
       vec[index]->add_Message(mes , dir ) ;

       writeMessages(ui->messageslist , layout , mes );

       ui->messagelineedit->clear();
       ui->messagelineedit->setFocus(Qt::OtherFocusReason);
       ui->messageslist->scrollToBottom();
    }
}

void homepage::vectroToList()
{
    QVector<QString> write;
    if(vec.empty())
        return;
    if(currentMode == PvMode)
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
    ui->messageslist->clear();

    QVector<QString>::iterator itt;
    for (itt = write.begin(); itt != write.end(); ++itt)
    {
        writeMessages(ui->messageslist , layout , *itt );
    }
}

void homepage::on_actionNew_group_triggered()
{
    on_newgroupbtn_clicked();
}


void homepage::on_newgroupbtn_clicked()
{
    creategroupdialog = new creategroup(howAmI, this);
    creategroupdialog->show();
    if(creategroupdialog->exec() == QDialog::Accepted)
    {
        int j = maindatabase::Creat_GroupID();
        QByteArray ba1 = creategroupdialog->getName().toLocal8Bit();
        const char *c_str21 = ba1.data();
        Group gr(howAmI , c_str21);
        gr.set_ID(j);
        gr.Make_NewGroupFile(gr.ExtractFileName(j));
        maindatabase::Add_Group(gr);
        maindatabase::Push_UserGroupID(j,howAmI);
        gr.add_Member(howAmI , gr.ExtractFileName(j));
        for(int i = 0 ; i < creategroupdialog->getCount() ; i++)
        {
            if(creategroupdialog->cheVec[i]->isChecked())
            {
                gr.add_Member(creategroupdialog->selected[i] , gr.ExtractFileName(j));
                maindatabase::Push_UserGroupID(j,creategroupdialog->selected[i]);
            }
        }

        Group obchat = Group::read_Group(j);

        QString s = obchat.get_GroupName();

        QListWidgetItem *item = setItemsInListWIdget(ui->listofusersgroupschanels , s);
        list.push_back(item);

        group = new Group  (obchat);
        vec.push_back(group);

        StoreGroup.push_back(obchat.get_ID());
        clicked_list_item(item);
    }
}
void homepage::on_actionNew_channel_triggered()
{
    on_newchannelbtn_clicked();
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
        channel obchat = channel::read_channel(j);
        QString s = obchat.get_ChannelName();

        QListWidgetItem *item = setItemsInListWIdget(ui->listofusersgroupschanels , s);
        list.push_back(item);

        channelOB = new channel(obchat);
        vec.push_back(channelOB);

        StoreChannel.push_back(obchat.get_ID());

        clicked_list_item(item);
    }
}


void homepage::on_infobtn_clicked()
{
    if(currentMode == GroupMode)
    {
        Group obchat = Group::read_Group(vec[index]->get_ID());
        infoGroup = new groupInfo(howAmI , obchat.get_Member() , obchat.get_ID(), this);
        infoGroup->show();

    }
    if(currentMode == ChannnelMode)
    {
        channel obchat = channel::read_channel(vec[index]->get_ID());
        infoChannel = new channelInfo(howAmI , obchat.get_Members() ,obchat.get_Admins(), obchat.get_ID(), this);
        infoChannel->show();
    }
    if(currentMode == PvMode)
    {
        pvchat obchat = pvchat::read_PVChat(vec[index]->get_ID());
        if(obchat.get_Addressee().get_ID() == howAmI.get_ID())
            infoPv = new PvInfo(howAmI , obchat.get_Owner(), this);
        else
            infoPv = new PvInfo(howAmI , obchat.get_Addressee(), this);
        infoPv->show();
    }
}

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

            QListWidgetItem *item = setItemsInListWIdget(ui->listofusersgroupschanels , s);
            list.push_back(item);

            channelOB = new channel(obchat);
            vec.push_back(channelOB);

            StoreChannel.push_back(obchat.get_ID());

        }
        checkThread = 1;
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

            QListWidgetItem *item = setItemsInListWIdget(ui->listofusersgroupschanels , s);
            list.push_back(item);

            group = new Group  (obchat);
            vec.push_back(group);

            StoreGroup.push_back(obchat.get_ID());

        }
        checkThread=1;
    }
    QVector<int> TemPv = howAmI.get_PVchatsID();
    int i2 = TemPv.size();
    int j2 = StorePv.size();
    if(i2 > j2)
    {
        for(int it2 = j2 ; it2 != i2 ; it2++ )
        {
            pvchat obchat = pvchat::read_PVChat(TemPv[it2]);
            QString s = obchat.get_Addressee().get_UserName();

            QListWidgetItem *item = setItemsInListWIdget(ui->listofusersgroupschanels , s);
            list.push_back(item);

            pv = new pvchat(obchat);
            vec.push_back(pv);
            StorePv.push_back(TemPv[it2]);

        }
        checkThread=1;
    }
}
void homepage::getMessage()
{
    whatIsNew();

    if(checkThread == 0)
        return;

    maindatabase::Find_user(howAmI);
    Display(isAdmin(howAmI));
}
bool homepage::isAdmin(user me)
{
    channel* ptr2 = dynamic_cast<channel*>(vec[index]);

    if(ptr2 == nullptr)
        return true;

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
    int i;   
    if(contactDialog->exec() == QDialog::Accepted)
    {

        for( i = 0 ; i < contactDialog->getCount() ; i++)
        {
            if(contactDialog->radVec[i]->isChecked())
            {
                for(int j = 0 ; j < PVs.size() ; j++)
                {
                    if(contactDialog->radSelcted[i].get_ID() == PVs[j].get_ID())
                    {

                        ptr = vec[j];
                        pvchat* ptr3 = dynamic_cast<pvchat*>(ptr);
                        if(ptr3 != nullptr)
                        {
                            clicked_list_item(list[j]);
                            return;
                        }
                    }
                }
                break;
            }

        }
        if(i == contactDialog->getCount())
            return;
        int j = maindatabase::Creat_PVChatID();
        pvchat gr(howAmI , contactDialog->radSelcted[i]);
        gr.set_ID(j);
        gr.Make_NewPVChatFile(gr.ExtractFileName(j));
        maindatabase::Add_PVChat(gr);
        maindatabase::Push_UserPVChatID(j,howAmI);
        maindatabase::Push_UserPVChatID(j,contactDialog->radSelcted[i]);

        pvchat obchat = pvchat::read_PVChat(j);
        QString s = obchat.get_Addressee().get_UserName();

        QListWidgetItem *item = setItemsInListWIdget(ui->listofusersgroupschanels , s);
        list.push_back(item);

        pv = new pvchat(obchat);
        vec.push_back(pv);
        StorePv.push_back(obchat.get_ID());

        clicked_list_item(item);
    }

}
void homepage::on_settingbtn_clicked()
{
    settingDialog = new Setting(howAmI, this);
    settingDialog->show();
    if(settingDialog->exec() == QDialog::Accepted)
    {
        homepage::close();
    }
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



