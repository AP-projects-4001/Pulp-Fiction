#include "pvinfo.h"
#include "ui_pvinfo.h"
#include "user.h"
#include "maindatabase.h"
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



    ui->usernamelineedit->setReadOnly(true);
    ui->biolineedit->setReadOnly(true);
    ui->firstnamelineedit->setReadOnly(true);
    ui->phonenumberlineedit->setReadOnly(true);
    ui->lastnamelineedit->setReadOnly(true);
    ui->emaillineedit->setReadOnly(true);
    ui->usernamelineedit->hide();
    ui->biolineedit->hide();
    ui->firstnamelineedit->hide();
    ui->phonenumberlineedit->hide();
    ui->lastnamelineedit->hide();
    ui->emaillineedit->hide();

    maindatabase::Find_user(you);
    qDebug() << "in pv info";
    qDebug() << you.getBioAccessibility();
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
        qDebug() << "isfriend";
    if(isFriend)
    {
        if(you.getNameAccessibility() != 2)
        {
            ui->usernamelineedit->show();
            QByteArray ba = you.get_UserName().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->usernamelineedit->setText(c_str2);
            ui->usernamelineedit->setReadOnly(true);
        }
        if(you.getPhoneAccessibility() != 2)
        {
            ui->phonenumberlineedit->show();
            QByteArray ba = you.get_PhoneNumber().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->phonenumberlineedit->setText(c_str2);
            ui->phonenumberlineedit->setReadOnly(true);
        }
        if(you.getEmailAccessibility() != 2)
        {
            ui->emaillineedit->show();
            QByteArray ba = you.get_EmailAddress().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->emaillineedit->setText(c_str2);
            ui->emaillineedit->setReadOnly(true);
        }
        if(you.getFirstNameAccessibility() != 2)
        {
            ui->firstnamelineedit->show();
            QByteArray ba = you.get_firstname().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->firstnamelineedit->setText(c_str2);
            ui->firstnamelineedit->setReadOnly(true);
        }
        if(you.getLastNameAccessibility() != 2)
        {
            ui->lastnamelineedit->show();
            QByteArray ba = you.get_lastname().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->lastnamelineedit->setText(c_str2);
            ui->lastnamelineedit->setReadOnly(true);
        }
    }

    else
    {

        if(you.getNameAccessibility() == 0)
        {
            ui->usernamelineedit->show();
            QByteArray ba = you.get_UserName().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->usernamelineedit->setText(c_str2);
            ui->usernamelineedit->setReadOnly(true);
        }
        if(you.getPhoneAccessibility() == 0)
        {
            ui->phonenumberlineedit->show();
            QByteArray ba = you.get_PhoneNumber().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->phonenumberlineedit->setText(c_str2);
            ui->phonenumberlineedit->setReadOnly(true);
        }

        if(you.getEmailAccessibility() == 0)
        {
            ui->emaillineedit->show();
            qDebug( )<< "you.you.getEmailAccessibility()()" << ' ' <<you.get_EmailAddress();
            QByteArray ba = you.get_EmailAddress().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->emaillineedit->setText(c_str2);
            ui->emaillineedit->setReadOnly(true);
        }
        if(you.getFirstNameAccessibility() == 0)
        {
            ui->firstnamelineedit->show();
            QByteArray ba = you.get_firstname().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->firstnamelineedit->setText(c_str2);
            ui->firstnamelineedit->setReadOnly(true);
        }
        if(you.getLastNameAccessibility() == 0)
        {
            ui->lastnamelineedit->show();
            QByteArray ba = you.get_lastname().toLocal8Bit();
            const char *c_str2 = ba.data();
            ui->lastnamelineedit->setText(c_str2);
            ui->lastnamelineedit->setReadOnly(true);
        }
        if(you.getPhotoAccessibility() == 0)
        {
            QString picDir = QCoreApplication::applicationDirPath()+"/../"+QString::number(you.get_ID())+".png";
            QString borderpic = "border-image: url(" + picDir + ");";
            QString styleSheet = "QLabel{" + borderpic +
                    "Padding: 1px;"
                    "Border-radius: 55px;"
                    "Color: #fefefe;"
                        "border-color: rgb(45, 135, 135);"
                    "border-style: solid;"
                     "border-width: 2px;}"

                    "QLabel:hover {"
                    "background-color: rgb(42, 46, 52);"
                    "border-style: solid;"
                     "border-width: 2px;"
                    "color: rgb(241, 182, 88);"
                    "border-color: rgb(245, 179, 1);}";

            ui->profilepicture->setStyleSheet(styleSheet);
        }
    }
}

PvInfo::~PvInfo()
{
    delete ui;
}

void PvInfo::on_backtohomepage_clicked()
{
    PvInfo::close();
}

