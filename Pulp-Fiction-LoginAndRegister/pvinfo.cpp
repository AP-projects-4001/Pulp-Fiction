#include "pvinfo.h"
#include "ui_pvinfo.h"
#include "user.h"
PvInfo::PvInfo(user me , user you , QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PvInfo)
{
    ui->setupUi(this);
    ui->label->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->lineEdit->hide();
    ui->lineEdit_2->hide();
    ui->lineEdit_3->hide();
    ui->lineEdit_4->hide();
    ui->lineEdit_5->hide();
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
            ui->label_2->show();
            QByteArray ba = you.get_UserName().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->lineEdit->setText(c_str2);
            ui->lineEdit->setReadOnly(true);
        }
        if(you.getPhoneAccessibility() != Nobody)
        {
            ui->label_3->show();
            QByteArray ba = you.get_PhoneNumber().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->lineEdit_2->setText(c_str2);
            ui->lineEdit_2->setReadOnly(true);
        }
        if(you.getEmailAccessibility() != Nobody)
        {
            ui->label_4->show();
            QByteArray ba = you.get_EmailAddress().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->lineEdit_3->setText(c_str2);
            ui->lineEdit_3->setReadOnly(true);
        }
        if(you.getFirstNameAccessibility() != Nobody)
        {
            ui->label_5->show();
            QByteArray ba = you.get_firstname().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->lineEdit_4->setText(c_str2);
            ui->lineEdit_4->setReadOnly(true);
        }
        if(you.getLastNameAccessibility() != Nobody)
        {
            ui->label_6->show();
            QByteArray ba = you.get_lastname().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->lineEdit_5->setText(c_str2);
            ui->lineEdit_5->setReadOnly(true);
        }
    }
    else
    {
        if(you.getNameAccessibility() != Nobody)
        {
            ui->label_2->show();
            QByteArray ba = you.get_UserName().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->lineEdit->setText(c_str2);
            ui->lineEdit->setReadOnly(true);
        }
        if(you.getPhoneAccessibility() == General)
        {
            ui->label_3->show();
            QByteArray ba = you.get_PhoneNumber().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->lineEdit_2->setText(c_str2);
            ui->lineEdit_2->setReadOnly(true);
        }
        if(you.getEmailAccessibility() == General)
        {
            ui->label_4->show();
            QByteArray ba = you.get_EmailAddress().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->lineEdit_3->setText(c_str2);
            ui->lineEdit_3->setReadOnly(true);
        }
        if(you.getFirstNameAccessibility() == General)
        {
            ui->label_5->show();
            QByteArray ba = you.get_firstname().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->lineEdit_4->setText(c_str2);
            ui->lineEdit_4->setReadOnly(true);
        }
        if(you.getLastNameAccessibility() == General)
        {
            ui->label_6->show();
            QByteArray ba = you.get_lastname().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->lineEdit_5->setText(c_str2);
            ui->lineEdit_5->setReadOnly(true);
        }
    }

}

PvInfo::~PvInfo()
{
    delete ui;
}
