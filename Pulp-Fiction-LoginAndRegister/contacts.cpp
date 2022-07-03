#include "contacts.h"
#include "ui_contacts.h"

Contacts::Contacts(user me ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Contacts)
{
    ui->setupUi(this);
    howAmI = me;
    ui->winstack->setCurrentIndex(0);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(20.0);
    bodyShadow->setDistance(6.0);
    bodyShadow->setColor(QColor(10, 5, 45, 80));
    ui->winstack->setGraphicsEffect(bodyShadow);
}

Contacts::~Contacts()
{
    delete ui;
}

void Contacts::on_newcontact_clicked()
{
    ui->winstack->setCurrentIndex(1);
}


void Contacts::on_searchcontact_textChanged(const QString &arg1)
{

}

void Contacts::on_backbtn_clicked()
{
    ui->winstack->setCurrentIndex(0);
}

void Contacts::on_backtohomepage2_clicked()
{
    Contacts::hide();
}

