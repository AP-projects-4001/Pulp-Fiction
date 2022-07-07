#include "groupinfo.h"
#include "ui_groupinfo.h"
#include "groupclass.h"
#include "maindatabase.h"
#include "countlessCalledFunctions.h"
groupInfo::groupInfo(user me ,QVector<user> members,int id , QWidget *parent) :
    QDialog(parent),
    ui(new Ui::groupInfo)
{
    ui->setupUi(this);
    idGroup = id;
    Groupmembers = members;
    ME = me;

    ui->userslistwidget->hide();
    ui->completebtn->hide();

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(20.0);
    bodyShadow->setDistance(4.0);
    bodyShadow->setColor(QColor(10, 5, 45, 80));
    ui->winstack->setGraphicsEffect(bodyShadow);
    ui->paticipantscount->setText(QString::number(members.size()));



    ui->memberslistwidget->setStyleSheet("background-color : rgba(0,0,0,50%); color : with;");
    QVector<user>::iterator itt;
    for (itt = Groupmembers.begin(); itt != Groupmembers.end(); ++itt)
    {
            QListWidgetItem* item = setItemsInListWIdget(ui->memberslistwidget , itt->get_UserName());
            item->setForeground(Qt::yellow);
            selectedList.push_back(*itt);
    }
}

groupInfo::~groupInfo()
{
    delete ui;
}

void groupInfo::on_backtohomepage_clicked()
{
    groupInfo::close();
}


void groupInfo::on_memberslistwidget_itemClicked(QListWidgetItem *item)
{
    for(int i = 0; i < ui->memberslistwidget->count(); ++i)
    {
        if(ui->memberslistwidget->item(i) == item)
        {
            infopv = new PvInfo(ME , selectedList[i] , this);
            infopv->show();
        }
    }
}


void groupInfo::on_addmemberbtn_clicked()
{
    ui->userslistwidget->show();
    ui->completebtn->show();
    cheVec.clear();
    selected.clear();
    QVector<user> everyBody = maindatabase::read_AllUsers();
    ui->userslistwidget->setStyleSheet("background-color : rgba(0,0,0,50%); color : white;");

    QVBoxLayout* layout = setQwidgetItemsInListWidget(ui->userslistwidget , 200 , 30);

    ui->userslistwidget->clear();
    QVector<user> ::Iterator itt;
    QVector<user> ::Iterator itt1;
    for (itt = everyBody.begin(); itt != everyBody.end(); ++itt) {
        int check = 0;
        for(itt1 = Groupmembers.begin() ; itt1 != Groupmembers.end() ; itt1++)
        {
            if(itt->get_ID() == itt1->get_ID())
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


void groupInfo::on_completebtn_clicked()
{
    Group gr = Group::read_Group(idGroup);
    for(int i = 0 ; i < ui->userslistwidget->count() ; i++)
    {
         if(cheVec[i]->isChecked())
         {
             gr.add_Member(selected[i] , gr.ExtractFileName(idGroup));
             maindatabase::Push_UserGroupID(idGroup,selected[i]);
             selected[i].add_GroupID(idGroup);
         }
    }
    groupInfo::hide();
}

