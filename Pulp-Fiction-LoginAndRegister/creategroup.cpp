#include "creategroup.h"
#include "countlessCalledFunctions.h"
#include "ui_creategroup.h"

creategroup::creategroup(user me ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::creategroup)
{
    ui->setupUi(this);
    howAmI = me;
    ui->winstack->setCurrentIndex(0);
    ui->groupname->clear();

    // Sets UI and shadow for it
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(20.0);
    bodyShadow->setDistance(4.0);
    bodyShadow->setColor(QColor(10, 5, 45, 80));
    ui->winstack->setGraphicsEffect(bodyShadow);

    write = maindatabase::read_AllUsers();
    ui->userslist->setStyleSheet("background-color : rgba(0,0,0,50%); color : black;");
    ui->userslist->clear();
    QVBoxLayout* layout = setQwidgetItemsInListWidget(ui->userslist , 200 , 30);

    QVector<user>::iterator itt;
    for (itt = write.begin(); itt != write.end(); ++itt) {
        if(itt->get_ID() != me.get_ID())
        {
            QCheckBox* text = writeCheckBox(ui->userslist , layout , itt->get_UserName());
            selected.push_back(*itt);
            cheVec.push_back(text);
        }
    }
    connect(ui->addbtn, &QPushButton::clicked,
            this, &creategroup::accept);
}

creategroup::~creategroup()
{
    delete ui;
}

void creategroup::on_submit_clicked()
{
    name = ui->groupname->text();
    ui->winstack->setCurrentIndex(1);
}
int creategroup::getCount()
{return ui->userslist->count();}

void creategroup::on_backbtn_5_clicked()
{
    ui->groupname->clear();
    ui->winstack->setCurrentIndex(0);
}
void creategroup::on_backbtn_3_clicked()
{
    creategroup::hide();
}
