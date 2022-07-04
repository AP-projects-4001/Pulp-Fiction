#include "channelinfo.h"
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

    ui->memberslistwidget->clear();
    if(Members.size() != 0)
    {
    QVector<user>::iterator itt;
    for (itt = Members.begin(); itt != Members.end(); ++itt) {

            QByteArray ba = itt->get_UserName().toLocal8Bit();
            const char *c_str2 = ba.data();
            QListWidgetItem* item = new QListWidgetItem;
            item->setText(c_str2);
            item->setForeground(Qt::yellow);
            ui->memberslistwidget->addItem(item);
            selectesList.push_back(*itt);
    }
    }
    else ui->memberslistwidget->hide();
    ui->adminslistwidget->setStyleSheet("background-color : rgba(0,0,0,50%); color : black;");
    ui->adminslistwidget->clear();
    QVector<user>::iterator itt1;
    for (itt1 = Admins.begin(); itt1 != Admins.end(); ++itt1) {

            QByteArray ba = itt1->get_UserName().toLocal8Bit();
            const char *c_str2 = ba.data();
            QListWidgetItem* item = new QListWidgetItem;
            item->setText(c_str2);
            item->setForeground(Qt::yellow);
            ui->adminslistwidget->addItem(item);
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
    qDebug() << "fjjf";
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
        ui->userslistwidget->show();
        ui->completebtn->show();
        currMode = AddAdmin;
        ui->userslistwidget->setStyleSheet("background-color : rgba(0,0,0,50%); color : white;");
        ui->userslistwidget->setFlow(QListView::LeftToRight);
        ui->userslistwidget->setGridSize(QSize(200, 30));
        ui->userslistwidget->setResizeMode(QListView::Adjust);
        ui->userslistwidget->setViewMode(QListView::ListMode);
        ui->userslistwidget->setWrapping(true);
        QVBoxLayout *layout = new QVBoxLayout;
        layout->setSizeConstraint(QLayout::SetMinimumSize);
        setLayout(layout);
        ui->userslistwidget->clear();
        QVector<user> ::Iterator itt;
        for (itt = Members.begin(); itt != Members.end(); ++itt) {
                auto item = new QListWidgetItem("", ui->userslistwidget);
                auto text = new QCheckBox;
                QByteArray ba = (itt->get_UserName()).toLocal8Bit();
                const char *c_str2 = ba.data();
                text->setText(c_str2);
                text->setStyleSheet("QCheckBox { background-color : rgba(0,0,0,0%); color : yellow; }");
                text->setMinimumSize(100, 20);
                text->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
                layout->addWidget(text);
                cheVec.push_back(text);
                selected.push_back(*itt);
                ui->userslistwidget->setItemWidget(item, text);

        }
        ui->completebtn->show();
}


void channelInfo::on_addmemberbtn_clicked()
{
        ui->userslistwidget->show();
        ui->completebtn->show();
        currMode = AddMember;
        QVector<user> everyBody = maindatabase::read_AllUsers();
        ui->userslistwidget->setStyleSheet("background-color : rgba(0,0,0,50%); color : white;");
        ui->userslistwidget->setFlow(QListView::LeftToRight);
        ui->userslistwidget->setGridSize(QSize(200, 30));
        ui->userslistwidget->setResizeMode(QListView::Adjust);
        ui->userslistwidget->setViewMode(QListView::ListMode);
        ui->userslistwidget->setWrapping(true);
        QVBoxLayout *layout = new QVBoxLayout;
        layout->setSizeConstraint(QLayout::SetMinimumSize);
        setLayout(layout);
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
                auto item = new QListWidgetItem("", ui->userslistwidget);
                auto text = new QCheckBox;
                QByteArray ba = (itt->get_UserName()).toLocal8Bit();
                const char *c_str2 = ba.data();
                text->setText(c_str2);
                text->setStyleSheet("QCheckBox { background-color : rgba(250,0,0,0%); color : yellow; }");
                text->setMinimumSize(100, 20);
                text->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
                layout->addWidget(text);
                cheVec.push_back(text);
                selected.push_back(*itt);
                ui->userslistwidget->setItemWidget(item, text);
            }
        }
        ui->completebtn->show();
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

