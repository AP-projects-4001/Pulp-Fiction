#include "newgroup.h"
#include "ui_newgroup.h"
#include <QVBoxLayout>
#include <QCheckBox>
#include "maindatabase.h"

newGroup::newGroup(user who,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newGroup)
{
    howAmI = who;
    ui->setupUi(this);
    write = maindatabase::read_AllUsers();
    for(int i = 0 ; i < write.count() ; i++)
    qDebug() << write[i].get_UserName();
    ui->listWidget->setStyleSheet("background-color : rgba(0,0,0,50%); color : black;");
    ui->listWidget->setFlow(QListView::LeftToRight);
    ui->listWidget->setGridSize(QSize(200, 30));
    ui->listWidget->setResizeMode(QListView::Adjust);
    ui->listWidget->setViewMode(QListView::ListMode);
    ui->listWidget->setWrapping(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSizeConstraint(QLayout::SetMinimumSize);
    setLayout(layout);
    ui->listWidget->clear();

    QVector<user>::iterator itt;
    for (itt = write.begin(); itt != write.end(); ++itt) {
        auto item = new QListWidgetItem("", ui->listWidget);
        auto text = new QCheckBox;
        QByteArray ba = (itt->get_UserName()).toLocal8Bit();
        const char *c_str2 = ba.data();
        text->setText(c_str2);
        text->setStyleSheet("QCheckBox { background-color : rgba(0,0,0,0%); color : white; }");
        text->setMinimumSize(100, 20);
        text->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        layout->addWidget(text);
        cheVec.push_back(text);
        ui->listWidget->setItemWidget(item, text);
    }
    connect(ui->pushButton, &QPushButton::clicked,
            this, &newGroup::accept);

}

newGroup::~newGroup()
{
    delete ui;
}
void newGroup::clickedMe()
{
    for(int i = 0 ; i < ui->listWidget->count() ; i++)
    {
        if(cheVec[i]->isChecked())
        {
            int i = maindatabase::Creat_GroupID();
            Group g(howAmI , "iut");
            g.Make_NewGroupFile(g.ExtractFileName(i));
            g.add_Member(write[i],g.get_GroupName());
            maindatabase::Add_Group(g);
            maindatabase::Push_UserGroupID(i,write[i]);
            maindatabase::Push_UserGroupID(i,howAmI);
        }
    }
}
int newGroup::getCount()const
{
    return ui->listWidget->count();
}

