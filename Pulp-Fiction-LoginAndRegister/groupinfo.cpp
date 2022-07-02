#include "groupinfo.h"
#include "ui_groupinfo.h"
#include "groupclass.h"
#include "maindatabase.h"
groupInfo::groupInfo(user me ,QVector<user> members,int id , QWidget *parent) :
    QDialog(parent),
    ui(new Ui::groupInfo)
{
    ME = me;
    idGroup = id;
    Groupmembers = members;
    ui->setupUi(this);
    ui->listWidget_2->hide();
    ui->pushButton_2->hide();
    ui->textEdit->setReadOnly(true);
    ui->pushButton->setText("Add member");
    QVector<user> ::Iterator itt;
    for (itt = members.begin(); itt != members.end(); ++itt) {
        QByteArray ba = itt->get_UserName().toLocal8Bit();
        const char *c_str2 = ba.data();
        ui->textEdit->insertPlainText(c_str2);
        ui->textEdit->insertPlainText("\n");
    }
    connect(ui->pushButton, &QPushButton::clicked,
         this, &groupInfo::add_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked,
         this, &groupInfo::ok_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked,
         this, &groupInfo::accept);
}

groupInfo::~groupInfo()
{
    delete ui;
}
void groupInfo::add_clicked()
{
    ui->listWidget_2->show();
    QVector<user> everyBody = maindatabase::read_AllUsers();
    ui->listWidget_2->setStyleSheet("background-color : rgba(250,0,0,50%); color : white;");
    ui->listWidget_2->setFlow(QListView::LeftToRight);
    ui->listWidget_2->setGridSize(QSize(200, 30));
    ui->listWidget_2->setResizeMode(QListView::Adjust);
    ui->listWidget_2->setViewMode(QListView::ListMode);
    ui->listWidget_2->setWrapping(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSizeConstraint(QLayout::SetMinimumSize);
    setLayout(layout);
    ui->listWidget_2->clear();
    QVector<user> ::Iterator itt;
    QVector<user> ::Iterator itt1;
    for (itt = everyBody.begin(); itt != everyBody.end(); ++itt) {
        int check = 0;
        if(itt->get_ID() == ME.get_ID())
        {
            check = 1;
        }
        else
        {
            for(itt1 = Groupmembers.begin() ; itt1 != Groupmembers.end() ; itt1++)
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
            auto item = new QListWidgetItem("", ui->listWidget_2);
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
            ui->listWidget_2->setItemWidget(item, text);
        }
    }
    ui->pushButton_2->show();
    ui->pushButton_2->setText("Ok");
}
void groupInfo::ok_clicked()
{
      Group gr = Group::read_Group(idGroup);
      qDebug() << idGroup;
      for(int i = 0 ; i < ui->listWidget_2->count() ; i++)
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
