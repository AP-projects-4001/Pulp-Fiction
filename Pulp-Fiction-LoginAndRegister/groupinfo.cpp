#include "groupinfo.h"
#include "ui_groupinfo.h"
#include "groupclass.h"
#include "maindatabase.h"
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
    for (itt = Groupmembers.begin(); itt != Groupmembers.end(); ++itt) {

            QByteArray ba = itt->get_UserName().toLocal8Bit();
            const char *c_str2 = ba.data();
            QListWidgetItem* item = new QListWidgetItem;
            item->setText(c_str2);
            item->setForeground(Qt::yellow);
            ui->memberslistwidget->addItem(item);
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
    }
}


void groupInfo::on_completebtn_clicked()
{
    Group gr = Group::read_Group(idGroup);
    qDebug() << idGroup;
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

