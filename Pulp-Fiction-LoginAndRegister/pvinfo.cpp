#include "pvinfo.h"
#include "ui_pvinfo.h"
#include "user.h"
#include "maindatabase.h"
void showInfo(QLineEdit* line , QString info)
{
    line->show();
    QByteArray ba = info.toLocal8Bit();
    const char *c_str2 = ba.data();
    line->setText(c_str2);
    line->setReadOnly(true);
}
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
    if(isFriend)
    {
        if(YOU.getNameAccessibility() != 2)
        {
            showInfo(ui->usernamelineedit , YOU.get_UserName());
        }
        if(YOU.getPhoneAccessibility() != 2)
        {
            showInfo(ui->phonenumberlineedit , YOU.get_PhoneNumber());
        }
        if(YOU.getBioAccessibility() != 2)
        {
            showInfo(ui->emaillineedit , YOU.get_Bio());
        }
        if(YOU.getEmailAccessibility() != 2)
        {
            showInfo(ui->emaillineedit , YOU.get_EmailAddress());
        }
        if(YOU.getFirstNameAccessibility() != 2)
        {
            showInfo(ui->firstnamelineedit , YOU.get_firstname());
        }
        if(YOU.getLastNameAccessibility() != 2)
        {
            showInfo(ui->lastnamelineedit , YOU.get_lastname());
        }
        if(YOU.getBioAccessibility() != 2)
        {
            showInfo(ui->biolineedit , YOU.get_Bio());
        }
        if(YOU.getPhotoAccessibility() != 2)
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

    else
    {

        if(YOU.getNameAccessibility() == 0)
        {
            showInfo(ui->usernamelineedit , YOU.get_UserName());
        }
        if(YOU.getPhoneAccessibility() == 0)
        {
            showInfo(ui->phonenumberlineedit , YOU.get_PhoneNumber());
        }

        if(YOU.getEmailAccessibility() == 0)
        {
            showInfo(ui->emaillineedit , YOU.get_EmailAddress());
        }
        if(YOU.getBioAccessibility() == 0)
        {
            showInfo(ui->emaillineedit , YOU.get_Bio());
        }
        if(YOU.getFirstNameAccessibility() == 0)
        {
            showInfo(ui->firstnamelineedit , YOU.get_firstname());
        }
        if(YOU.getLastNameAccessibility() == 0)
        {
            showInfo(ui->lastnamelineedit , YOU.get_lastname());
        }
        if(YOU.getBioAccessibility() == 0)
        {
            showInfo(ui->biolineedit , YOU.get_Bio());
        }
        if(YOU.getPhotoAccessibility() == 0)
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

