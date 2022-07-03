#include "pvinfo.h"
#include "ui_pvinfo.h"
#include "user.h"
PvInfo::PvInfo(user me , user you , QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PvInfo)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(20.0);
    bodyShadow->setDistance(4.0);
    bodyShadow->setColor(QColor(10, 5, 45, 80));
    ui->winstack->setGraphicsEffect(bodyShadow);

    ui->username->hide();
    ui->firstname->hide();
    ui->lastname->hide();
    ui->phonenumber->hide();
    ui->email->hide();
    ui->profilepicture->hide();
    bool isFriend = false;
    QVector<int> :: iterator it;
    for(it = you.get_FriendsID().begin() ; it != you.get_FriendsID().end() ; it++)
    {
        if(*it == me.get_ID())
        {
            isFriend = true;
            break;
        }
    }
    if(isFriend)
    {
        if(you.getNameAccessibility() != Nobody)
        {
            ui->username->show();
            QByteArray ba = you.get_UserName().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->usernamelineedit->setText(c_str2);
            ui->usernamelineedit->setReadOnly(true);
        }
        if(you.getPhoneAccessibility() != Nobody)
        {
            ui->phonenumber->show();
            QByteArray ba = you.get_PhoneNumber().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->phonenumberlineedit->setText(c_str2);
            ui->phonenumberlineedit->setReadOnly(true);
        }
        if(you.getEmailAccessibility() != Nobody)
        {
            ui->email->show();
            QByteArray ba = you.get_EmailAddress().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->emaillineedit->setText(c_str2);
            ui->emaillineedit->setReadOnly(true);
        }
        if(you.getFirstNameAccessibility() != Nobody)
        {
            ui->firstname->show();
            QByteArray ba = you.get_firstname().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->firstnamelineedit->setText(c_str2);
            ui->firstnamelineedit->setReadOnly(true);
        }
        if(you.getLastNameAccessibility() != Nobody)
        {
            ui->lastname->show();
            QByteArray ba = you.get_lastname().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->lastnamelineedit->setText(c_str2);
            ui->lastnamelineedit->setReadOnly(true);
        }
    }
    else
    {
        if(you.getNameAccessibility() != Nobody)
        {
            ui->username->show();
            QByteArray ba = you.get_UserName().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->usernamelineedit->setText(c_str2);
            ui->usernamelineedit->setReadOnly(true);
        }
        if(you.getPhoneAccessibility() == General)
        {
            ui->phonenumber->show();
            QByteArray ba = you.get_PhoneNumber().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->phonenumberlineedit->setText(c_str2);
            ui->phonenumberlineedit->setReadOnly(true);
        }
        if(you.getEmailAccessibility() == General)
        {
            ui->email->show();
            QByteArray ba = you.get_EmailAddress().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->emaillineedit->setText(c_str2);
            ui->emaillineedit->setReadOnly(true);
        }
        if(you.getFirstNameAccessibility() == General)
        {
            ui->firstname->show();
            QByteArray ba = you.get_firstname().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->firstnamelineedit->setText(c_str2);
            ui->firstnamelineedit->setReadOnly(true);
        }
        if(you.getLastNameAccessibility() == General)
        {
            ui->lastname->show();
            QByteArray ba = you.get_lastname().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->lastnamelineedit->setText(c_str2);
            ui->lastnamelineedit->setReadOnly(true);
        }
    }
}

PvInfo::~PvInfo()
{
    delete ui;
}

void PvInfo::on_backtohomepage_clicked()
{
    PvInfo::hide();
}

