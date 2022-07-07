#include "createchannel.h"
#include "countlessCalledFunctions.h"
#include "ui_createchannel.h"
#include "maindatabase.h"
createchannel::createchannel(user me ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createchannel)
{
    ui->setupUi(this);
    howAmI = me;
    ui->winstack->setCurrentIndex(0);
    ui->channelname->clear();

    // Sets UI and shadow for it
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(20.0);
    bodyShadow->setDistance(4.0);
    bodyShadow->setColor(QColor(10, 5, 45, 80));
    ui->winstack->setGraphicsEffect(bodyShadow);

    setChecks();
    connect(ui->addbtn, &QPushButton::clicked,
            this, &createchannel::accept);
}

createchannel::~createchannel()
{
    delete ui;
}

void createchannel::on_submit_clicked()
{
    name = ui->channelname->text();    
    if(name.isEmpty())
        QMessageBox::warning(this, "invalid name", "please enter a name for your channel");
    else
    {
        ui->winstack->setCurrentIndex(1);
        setChecks();
    }
}
int createchannel::getCount()
{return ui->userslist->count();}

void createchannel::on_backbtn_5_clicked()
{
    ui->channelname->clear();
    ui->winstack->setCurrentIndex(0);
}
void createchannel::on_backbtn_3_clicked()
{
    createchannel::hide();
}
void createchannel::setChecks()
{
    write.clear();
    selected.clear();
    cheVec.clear();
    write = maindatabase::read_AllUsers();
    for(int i = 0 ; i < write.count() ; i++)
    ui->userslist->setStyleSheet("background-color : rgba(0,0,0,50%); color : black;");
    QVBoxLayout* layout = setQwidgetItemsInListWidget(ui->userslist , 200 , 30);
    ui->userslist->clear();

    QVector<user>::iterator itt;
    for (itt = write.begin(); itt != write.end(); ++itt) {
        if(itt->get_ID() != howAmI.get_ID())
        {
            QCheckBox* text = writeCheckBox(ui->userslist , layout , itt->get_UserName());
            selected.push_back(*itt);
            cheVec.push_back(text);
        }
    }
}
