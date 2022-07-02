#include "setting.h"
#include "ui_setting.h"
#include "customshadoweffect.h"
#include <QMessageBox>

Setting::Setting(user me ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    ui->usernameeditprofile->setReadOnly(true);
    ui->phoneeditprofile->setReadOnly(true);
    ui->emaileditprofile->setReadOnly(true);
    ui->winstack->setCurrentIndex(0);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(20.0);
    bodyShadow->setDistance(4.0);
    bodyShadow->setColor(QColor(10, 5, 45, 80));
    ui->winstack->setGraphicsEffect(bodyShadow);

    QIntValidator* intValidator = new QIntValidator;
    ui->phoneeditprofile->setValidator(intValidator);

    howAmI = me;
//    ui->profilepicture_2->setPixmap(QPixmap("file:///C://Users//tejarat pooya//Pictures//Desktop//AP project//build-APproject-Desktop_Qt_6_2_4_MinGW_64_bit-Debug//masih.png"));

//    QString useridstr = "Your Id is: " + QString::number(me.get_ID());
    ui->userideditprofile->setText(QString::number(howAmI.get_ID()));
    ui->userusernameforsettinglbl->setText(howAmI.get_UserName());
    ui->firstnameeditprofile->setText(howAmI.get_firstname()); // Not working ??
    ui->passwordeditprofile->setText(howAmI.get_Password());
    ui->usernameeditprofile->setText(howAmI.get_UserName());
    ui->lastnameeditprofile->setText(howAmI.get_lastname()); // Not working ??
    ui->phoneeditprofile->setText(howAmI.get_PhoneNumber());
    ui->emaileditprofile->setText(howAmI.get_EmailAddress());
    QDate Date = QDate::fromString(howAmI.get_BirthDate(),"M/d/yyyy");
    qDebug() << Date;
    ui->birthdateeditprofile->setDate(Date);
}

Setting::~Setting()
{

    delete ui;
}

void Setting::on_editprofile_clicked()
{
    ui->winstack->setCurrentIndex(1);
}


void Setting::on_backtohomepage_clicked()
{
    Setting::hide();
}


void Setting::on_backbtn_clicked()
{
    ui->winstack->setCurrentIndex(0);
}


void Setting::on_editprivacy_clicked()
{
    ui->winstack->setCurrentIndex(2);
}


void Setting::on_backbtn_2_clicked()
{
    ui->winstack->setCurrentIndex(0);
}


void Setting::on_showpassforeditprofile_stateChanged(int arg1)
{
    if(arg1)
        ui->passwordeditprofile->setEchoMode(QLineEdit::Normal);
    else
        ui->passwordeditprofile->setEchoMode(QLineEdit::Password);
}


void Setting::on_savebtn_clicked()
{
    bool halt = false;


    if(ui->usernameeditprofile->text() == "")
    {
        ui->usernameeditprofile->setPlaceholderText("Username EMPTY!");
        halt = true;
    }

    if(ui->passwordeditprofile->text() == "")
    {
        ui->passwordeditprofile->setPlaceholderText("Password EMPTY!");
        halt = true;
    }

    if(ui->emaileditprofile->text() == "")
    {
        ui->emaileditprofile->setPlaceholderText("E-mail EMPTY!");
        halt = true;
    }

    if(ui->firstnameeditprofile->text() == "")
    {
        ui->firstnameeditprofile->setPlaceholderText("First Name EMPTY!");
        halt = true;
    }

    if(ui->phoneeditprofile->text() == "")
    {
        ui->phoneeditprofile->setPlaceholderText("Phone is EMPTY!");
        halt = true;
    }

    if(ui->lastnameeditprofile->text() == "")
    {
        ui->lastnameeditprofile->setPlaceholderText("Last Name EMPTY!");
        halt = true;
    }
    if(!ui->emaileditprofile->text().contains("@"))
    {
        ui->emaileditprofile->setText("");
        ui->emaileditprofile->setPlaceholderText("Enter a valid E-mail!");
        halt = true;
    }


    if(halt)
    {
        ui->Status->setText("<b color:#33>Please correct your mistakes.</b>");
    }
    else
    {
        QString username, password, firstnamee, lastname, phone, email, birthdate;
        username = ui->usernameeditprofile->text();
        password = ui->passwordeditprofile->text();
        firstnamee = ui->firstnameeditprofile->text();
        lastname = ui->lastnameeditprofile->text();
        phone = ui->phoneeditprofile->text();
        email = ui->emaileditprofile->text();
        birthdate = ui->birthdateeditprofile->text();

        if(password.size() < 4)
        {
            ui->passwordeditprofile->clear();
            QMessageBox::warning(this, "Warnning", "password must have at least 4 characters");
        }
        bool hasUppercase = false;
        bool hasNumber = false;
        for (int x = 0; x < password.length(); x++)
        {
            if (password[x] >= 'A' && password[x] < 'Z')
            {
                hasUppercase = true;
            }
            if (password[x] >= '0' && password[x] < '9')
            {
                hasNumber = true;
            }
        }
        // condition to check if password met the 2 requirements for including an uppercase letter and a number
        if (!hasNumber || !hasUppercase)
        {
            QMessageBox::warning(this,"Warning", "Password must include atleast 1 uppercase letter and atleast 1 number");
            ui->passwordeditprofile->clear();
        }
        if(!maindatabase::Check_username(username))
        {
            QMessageBox::warning(this,"Duplicate username", "Oh no! We have your username in our database choose another one please!");
            ui->usernameeditprofile->clear();
        }
        if(!maindatabase::Check_EmailAddress(email))
        {
            QMessageBox::warning(this,"Duplicate email", "Oh no! We have your email in our database choose another one please!");
            ui->emaileditprofile->clear();
        }
        if(!maindatabase::Check_PhoneNumber(phone))
        {
            QMessageBox::warning(this,"Duplicate phone", "Oh no! We have your phone in our database choose another one please!");
            ui->phoneeditprofile->clear();
        }

        bool username1, password1, phone1, email1;
        username1 = ui->usernameeditprofile->text().size();
        password1 = ui->passwordeditprofile->text().size();
        phone1 = ui->phoneeditprofile->text().size();
        email1 = ui->emaileditprofile->text().size();

        if(username1 && password1 && phone1 && email1)
        {
            user userRegister;
            userRegister.set_ID(maindatabase::Creat_ID());
            userRegister.set_UserName(username);
            userRegister.set_Password(password);
            userRegister.set_EmailAddress(email);
            userRegister.set_Firstname(firstnamee);
            userRegister.set_Lastname(lastname);
            userRegister.set_BirthDate(birthdate);
            userRegister.set_PhoneNumber(phone);


//            database->Add_user(userRegister);

//            if (this->picName != "")
//            {
////                QString to = this->picDir+"/"+ui->usernameRegister->text();

////                if (QFile::exists(to))
////                {
////                    QFile::remove(to);
////                }

////                QFile::copy(this->picName, to);
////                this->picName = "";
//                QString path = userRegister.get_UserName() + ".png";
//                qDebug() << path;
//                qDebug() << userRegister.get_UserName();
//                ui->rpLabel->grab().save(path);

//            }

//            ui->regLabel->setText("");
//            ui->usernameRegister->setText("");
//            ui->passwordRegister->setText("");
//            ui->passwordRegister_2->setText("");
//            ui->emailRegister->setText("");
//            ui->firstnameRegister->setText("");
//            ui->lastnameRegister->setText("");
//            ui->phoneRegister->setText("");
//            ui->showpassforsignup->setChecked(false);
//            ui->rpLabel->setText("<img src=\":/img/img/user.png\" />");
//            ui->loginLabel->setText("Registration Successful! You can now login.");
//            ui->usernameBox->setText(inneruser.get_UserName());
//            ui->passwordBox->setText(inneruser.get_Password());
//            ui->winStack->setCurrentIndex(0);
        }
    }
}

