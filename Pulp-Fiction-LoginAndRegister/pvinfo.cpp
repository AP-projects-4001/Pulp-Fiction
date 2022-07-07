#include "pvinfo.h"
#include "ui_pvinfo.h"
#include "user.h"
#include "maindatabase.h"
#include <QLineEdit>
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

    user YOU = maindatabase::getUserdetails(you.get_ID());
    bool isFriend = false;
    QVector<int> :: iterator it;
    for(it = YOU.get_FriendsID().begin() ; it != YOU.get_FriendsID().end() ; it++)
    {
        if(*it == me.get_ID())
        {
            isFriend = true;
            break;
        }
    }
    qDebug() << "gjgjjg";
    this->showInfo(YOU.getNameAccessibility() ,isFriend , ui->usernamelineedit , YOU.get_UserName());
    this->showInfo(YOU.getPhoneAccessibility() ,isFriend , ui->phonenumberlineedit , YOU.get_PhoneNumber());
    showInfo(YOU.getBioAccessibility() ,isFriend , ui->biolineedit , YOU.get_Bio());
    showInfo(YOU.getEmailAccessibility() ,isFriend , ui->emaillineedit , YOU.get_EmailAddress());
    showInfo(YOU.getFirstNameAccessibility() ,isFriend , ui->firstnamelineedit , YOU.get_firstname());
    showInfo(YOU.getLastNameAccessibility() ,isFriend , ui->lastnamelineedit , YOU.get_lastname());

    if(YOU.getPhotoAccessibility() != 2)
    {
        if(YOU.getPhotoAccessibility() == 1 && isFriend)
        {
            QString picDir = QCoreApplication::applicationDirPath()+"/../"+QString::number(YOU.get_ID())+".png";
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
        }else if(YOU.getPhotoAccessibility() == 0)
        {
            QString picDir = QCoreApplication::applicationDirPath()+"/../"+QString::number(YOU.get_ID())+".png";
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

void PvInfo::showInfo(int check ,bool isFriend , QLineEdit* line , QString info)
{
    if(check == 2)
    {
        return;
    }
    else if(check == 1 && !(isFriend))
        return;
    qDebug() << "ggjgj";
    line->show();
    QByteArray ba = info.toLocal8Bit();
    const char *c_str2 = ba.data();
    line->setText(c_str2);
    line->setReadOnly(true);


}
