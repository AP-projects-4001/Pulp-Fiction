#include "channelinfo.h"
#include "countlessCalledFunctions.h"
#include "ui_channelinfo.h"
#include "maindatabase.h"
#include <QCheckBox>
channelInfo::channelInfo(user me , QVector<user> member,QVector<user> admin, int id,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::channelInfo)
{
    ui->setupUi(this);
    Me = me;
    Members = member;
    Admins = admin;
    idChannel = id;
    ui->userslistwidget->hide();
    ui->completebtn->hide();

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(20.0);
    bodyShadow->setDistance(4.0);
    bodyShadow->setColor(QColor(10, 5, 45, 80));
    ui->winstack->setGraphicsEffect(bodyShadow);
    int participants = member.size() + admin.size();
    ui->paticipantscount->setText(QString::number(participants));

    if(Members.size() != 0)
    {
        QVector<user>::iterator itt;
        for (itt = Members.begin(); itt != Members.end(); ++itt)
        {
            QListWidgetItem* item = setItemsInListWIdget(ui->memberslistwidget , itt->get_UserName());
            item->setForeground(Qt::yellow);
            selectesList.push_back(*itt);
        }
    }
    else
        ui->memberslistwidget->hide();

    ui->adminslistwidget->setStyleSheet("background-color : rgba(0,0,0,50%); color : black;");

    QVector<user>::iterator itt1;
    for (itt1 = Admins.begin(); itt1 != Admins.end(); ++itt1)
    {
        QListWidgetItem* item = setItemsInListWIdget(ui->adminslistwidget , itt1->get_UserName());
        item->setForeground(Qt::yellow);
            selectesList.push_back(*itt1);
    }
}

channelInfo::~channelInfo()
{
    delete ui;
}


void channelInfo::on_backtohomepage_clicked()
{
    channelInfo::close();
}


void channelInfo::on_adminslistwidget_itemClicked(QListWidgetItem *item)
{
    for(int i = 0; i < ui->adminslistwidget->count(); ++i)
    {
        if(ui->adminslistwidget->item(i) == item)
        {
            infopv = new PvInfo(Me , selectesList[Members.size()+i] , this);
            infopv->show();
        }
    }
}
void channelInfo::on_memberslistwidget_itemClicked(QListWidgetItem *item)
{
    for(int i = 0; i < ui->memberslistwidget->count(); ++i)
    {
        if(ui->memberslistwidget->item(i) == item)
        {
            infopv = new PvInfo(Me , selectesList[i] , this);
            infopv->show();
        }
    }
}

void channelInfo::on_addadminbtn_clicked()
{
        cheVec.clear();
        selected.clear();

        ui->userslistwidget->show();
        ui->userslistwidget->clear();
        ui->completebtn->show();
        ui->addmemberbtn->hide();

        currMode = AddAdmin;

        ui->userslistwidget->setStyleSheet("background-color : rgba(0,0,0,50%); color : white;");
        QVBoxLayout* layout = setQwidgetItemsInListWidget(ui->userslistwidget , 200 , 30);

        QVector<user> ::Iterator itt;
        for (itt = Members.begin(); itt != Members.end(); ++itt)
        {
            QCheckBox* text = writeCheckBox(ui->userslistwidget , layout , itt->get_UserName() );
            cheVec.push_back(text);
            selected.push_back(*itt);
        }


}


void channelInfo::on_addmemberbtn_clicked()
{
        cheVec.clear();
        selected.clear();

        ui->userslistwidget->show();
        ui->completebtn->show();
        ui->addadminbtn->hide();

        currMode = AddMember;

        QVector<user> everyBody = maindatabase::read_AllUsers();

        ui->userslistwidget->setStyleSheet("background-color : rgba(0,0,0,50%); color : white;");
        QVBoxLayout* layout = setQwidgetItemsInListWidget(ui->userslistwidget , 200 , 30);
        ui->userslistwidget->clear();

        QVector<user> ::Iterator itt;
        QVector<user> ::Iterator itt1;
        QVector<user> ::Iterator itt2;
        for (itt = everyBody.begin(); itt != everyBody.end(); ++itt) {
            int check = 0;
            for(itt1 = Members.begin() ; itt1 != Members.end() ; itt1++)
            {
                if(itt->get_ID() == itt1->get_ID())
                {
                      check = 1;
                      break;
                 }
             }
            for(itt2 = Admins.begin() ; itt2 != Admins.end() ; itt2++)
            {
                if(itt->get_ID() == itt2->get_ID())
                {
                      check = 1;
                      break;
                 }
             }
            if(check == 0)
            {
                QCheckBox* text = writeCheckBox(ui->userslistwidget , layout , itt->get_UserName() );
                cheVec.push_back(text);
                selected.push_back(*itt);
            }
        }
}

void channelInfo::on_completebtn_clicked()
{
    if(currMode == AddMember)
    {
         channel gr = channel::read_channel(idChannel);
         for(int i = 0 ; i < ui->userslistwidget->count() ; i++)
         {
              if(cheVec[i]->isChecked())
              {
                   gr.add_Member(selected[i] , gr.ExtractFileName(idChannel));
                   maindatabase::Push_UserChannelID(idChannel,selected[i]);
                   selected[i].add_ChannelID(idChannel);
              }
         }
         channelInfo::hide();
    }
    else
    {
        channel gr = channel::read_channel(idChannel);
        for(int i = 0 ; i < ui->userslistwidget->count() ; i++)
        {
             if(cheVec[i]->isChecked())
             {
                  gr.delete_Member(selected[i] , gr.ExtractFileName(idChannel)) ;
                  gr.add_Admins(selected[i] , gr.ExtractFileName(idChannel));
             }
        }
        channelInfo::hide();
    }
}

