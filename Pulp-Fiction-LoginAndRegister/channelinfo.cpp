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
    ui->listWidget->hide();
    ui->pushButton_3->hide();
    ui->textEdit->setReadOnly(true);
    ui->pushButton->setText("Add member");
    ui->pushButton_2->setText("Add admin");
    ui->pushButton_3->setText("Ok");
    ui->textEdit->insertPlainText("Members:\n");
    QVector<user> ::Iterator itt1;
    for (itt1 = member.begin(); itt1 != member.end(); ++itt1) {
        QByteArray ba = itt1->get_UserName().toLocal8Bit();
        const char *c_str2 = ba.data();
        ui->textEdit->insertPlainText(c_str2);
        ui->textEdit->insertPlainText("\n");
    }
    ui->textEdit_2->insertPlainText("Admins:\n");
    QVector<user> ::Iterator itt;
    for (itt = Admins.begin(); itt != Admins.end(); ++itt) {
        QByteArray ba = itt->get_UserName().toLocal8Bit();
        const char *c_str2 = ba.data();
        ui->textEdit_2->insertPlainText(c_str2);
        ui->textEdit_2->insertPlainText("\n");
    }
}

channelInfo::~channelInfo()
{
    delete ui;
}

void channelInfo::on_pushButton_clicked()
{
    ui->listWidget->show();
    ui->pushButton_3->show();
    ui->pushButton_3->setText("Ok");
    currMode = AddMember;
    QVector<user> everyBody = maindatabase::read_AllUsers();
    ui->listWidget->setStyleSheet("background-color : rgba(250,0,0,50%); color : white;");
    ui->listWidget->setFlow(QListView::LeftToRight);
    ui->listWidget->setGridSize(QSize(200, 30));
    ui->listWidget->setResizeMode(QListView::Adjust);
    ui->listWidget->setViewMode(QListView::ListMode);
    ui->listWidget->setWrapping(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSizeConstraint(QLayout::SetMinimumSize);
    setLayout(layout);
    ui->listWidget->clear();
    QVector<user> ::Iterator itt;
    QVector<user> ::Iterator itt1;
    for (itt = everyBody.begin(); itt != everyBody.end(); ++itt) {
        int check = 0;
        if(itt->get_ID() == Me.get_ID())
        {
            check = 1;
        }
        else
        {
            for(itt1 = Members.begin() ; itt1 != Members.end() ; itt1++)
            {
                if(itt->get_ID() == itt1->get_ID())
                {
                    check = 1;
                    break;
                }
            }
        }
        if(check == 0)
        {
            auto item = new QListWidgetItem("", ui->listWidget);
            auto text = new QCheckBox;
            QByteArray ba = (itt->get_UserName()).toLocal8Bit();
            const char *c_str2 = ba.data();
            text->setText(c_str2);
            text->setStyleSheet("QCheckBox { background-color : rgba(250,0,0,0%); color : white; }");
            text->setMinimumSize(100, 20);
            text->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            layout->addWidget(text);
            cheVec.push_back(text);
            selected.push_back(*itt);
            ui->listWidget->setItemWidget(item, text);
        }
    }

}


void channelInfo::on_pushButton_2_clicked()
{
    ui->listWidget->show();
    ui->pushButton_3->show();
    ui->pushButton_3->setText("Ok");
    currMode = AddAdmin;
    ui->listWidget->setStyleSheet("background-color : rgba(250,0,0,50%); color : white;");
    ui->listWidget->setFlow(QListView::LeftToRight);
    ui->listWidget->setGridSize(QSize(200, 30));
    ui->listWidget->setResizeMode(QListView::Adjust);
    ui->listWidget->setViewMode(QListView::ListMode);
    ui->listWidget->setWrapping(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSizeConstraint(QLayout::SetMinimumSize);
    setLayout(layout);
    ui->listWidget->clear();
    QVector<user> ::Iterator itt;
    for (itt = Members.begin(); itt != Members.end(); ++itt) {
        int check = 0;
        if(itt->get_ID() == Me.get_ID())
        {
            check = 1;
        }
        if(check == 0)
        {
            auto item = new QListWidgetItem("", ui->listWidget);
            auto text = new QCheckBox;
            QByteArray ba = (itt->get_UserName()).toLocal8Bit();
            const char *c_str2 = ba.data();
            text->setText(c_str2);
            text->setStyleSheet("QCheckBox { background-color : rgba(250,0,0,0%); color : white; }");
            text->setMinimumSize(100, 20);
            text->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            layout->addWidget(text);
            cheVec.push_back(text);
            selected.push_back(*itt);
            ui->listWidget->setItemWidget(item, text);
        }
    }

}
//void groupInfo::ok_clicked()
//{
//      Group gr = Group::read_Group(idGroup);
//      qDebug() << idGroup;
//      for(int i = 0 ; i < ui->listWidget_2->count() ; i++)
//      {
//           if(cheVec[i]->isChecked())
//           {
//               gr.add_Member(selected[i] , gr.ExtractFileName(idGroup));
//               maindatabase::Push_UserGroupID(idGroup,selected[i]);
//               selected[i].add_GroupID(idGroup);
//           }
//      }
//      groupInfo::hide();
//}

void channelInfo::on_pushButton_3_clicked()
{
    if(currMode == AddMember)
    {
         channel gr = channel::read_channel(idChannel);
              qDebug() << idChannel;
         for(int i = 0 ; i < ui->listWidget->count() ; i++)
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
             qDebug() << idChannel;
        for(int i = 0 ; i < ui->listWidget->count() ; i++)
        {
             if(cheVec[i]->isChecked())
             {
                  gr.add_Admins(selected[i] , gr.ExtractFileName(idChannel));
             }
        }
        channelInfo::hide();
    }
}

