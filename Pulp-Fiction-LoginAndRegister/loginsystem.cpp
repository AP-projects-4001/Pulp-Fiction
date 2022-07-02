#include "loginsystem.h"
#include "ui_loginsystem.h"
#include <QFileDialog>
#include <QMessageBox>
#include <homepage.h>
#include <QDebug>

#include "setting.h"

LoginSystem::LoginSystem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginSystem)
{
    ui->setupUi(this);
    database = new maindatabase();
    ui->winStack->setCurrentIndex(0);

    ui->passwordBox->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    ui->passwordRegister->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    QIntValidator* intValidator = new QIntValidator;
    ui->phoneRegister->setValidator(intValidator);
}

LoginSystem::~LoginSystem()
{
    delete ui;
}

void LoginSystem::on_loginButton_clicked()
{
    this->loggedIn = Login(ui->usernameBox->text(), ui->passwordBox->text());

    if(this->loggedIn)
    {
        this->username = ui->usernameBox->text();
        this->password = ui->passwordBox->text();

        ui->loginLabel->setText("");
        user u;
        u.set_UserName("sara");
        pvchat ob(inneruser , u);

        int t = maindatabase::Creat_PVChatID();
        ob.set_ID(t);
        ob.Make_NewPVChatFile(ob.ExtractFileName(t));
        ob.add_Message("hello" , ob.ExtractFileName(t));
        ob.add_Message("salam" , ob.ExtractFileName(t));
        ob.add_Message("areyouok" , ob.ExtractFileName(t));
        maindatabase::Push_UserPVChatID(ob.get_ID(),inneruser);
        maindatabase::Add_PVChat(ob);

        user u1;
        u1.set_UserName("negar");
        pvchat ob1(inneruser , u1);
        int t1 = maindatabase::Creat_PVChatID();
        ob1.set_ID(t1);
        ob1.Make_NewPVChatFile(ob1.ExtractFileName(t1));
        ob1.add_Message("bye" , ob1.ExtractFileName(t1));

        maindatabase::Push_UserPVChatID(ob1.get_ID(),inneruser);
        maindatabase::Add_PVChat(ob1);
        /**group**/
        int i = maindatabase::Creat_GroupID();
        Group g(inneruser , "iut");
        g.Make_NewGroupFile(g.ExtractFileName(i));
        g.add_Member(u,g.get_GroupName());
        maindatabase::Add_Group(g);
        maindatabase::Push_UserGroupID(i,u);
        maindatabase::Push_UserGroupID(i,inneruser);
        g.add_Message("bye" , g.ExtractFileName(i));
        g.add_Message("hello" , g.ExtractFileName(i));
        /**channel**/
        int i1 = maindatabase::Creat_ChannelID();
        channel g1(inneruser , "channel");
        g1.Make_NewChannelFile(g1.ExtractFileName(i1));
        g1.add_Member(u,g1.get_ChannelName());
        maindatabase::Add_Channel(g1);
        maindatabase::Push_UserChannelID(i1,u);
        maindatabase::Push_UserChannelID(i1,inneruser);
        g1.add_Message("fjfjjfj" , g1.ExtractFileName(i1));
        g1.add_Message("fjjfjfjfjfjfjjf" , g1.ExtractFileName(i1));
        g1.add_Admins(inneruser,g1.get_ChannelName());
        inneruser.add_ChannelID(i1);

        QPixmap pixmap1(":/img/img/icons8-login-64.png");
        ui->loginpic->setPixmap(pixmap1);
        delay(1); // Delay window for setting new picture on label
        LoginSystem::hide();
        hmpg = new homepage(inneruser);
        hmpg->show();
//        Setting *settingdialog = new Setting(inneruser, this);
//        settingdialog->show();
    }
    else
    {
        ui->loginLabel->setText("Login failed: Invalid credentials!");
    }
}

bool LoginSystem::Login(QString u, QString p)
{
    inneruser.set_UserName(u);
    inneruser.set_Password(p);
    if(maindatabase::Find_user(inneruser))
        return true;
    return false;
}

void LoginSystem::on_regButton_clicked()
{
    ui->winStack->setCurrentIndex(1);
}

void LoginSystem::on_completeRegButton_clicked()
{
    bool halt = false;


    if(ui->usernameRegister->text() == "")
    {
        ui->usernameRegister->setPlaceholderText("Username EMPTY!");
        halt = true;
    }

    if(ui->passwordRegister->text() == "")
    {
        ui->passwordRegister->setPlaceholderText("Password EMPTY!");
        halt = true;
    }
    if(ui->passwordRegister_2->text() == "")
    {
        ui->passwordRegister_2->setPlaceholderText("Second Password EMPTY!");
        halt = true;
    }

    if(ui->emailRegister->text() == "")
    {
        ui->emailRegister->setPlaceholderText("E-mail EMPTY!");
        halt = true;
    }

    if(ui->firstnameRegister->text() == "")
    {
        ui->firstnameRegister->setPlaceholderText("First Name EMPTY!");
        halt = true;
    }

    if(ui->phoneRegister->text() == "")
    {
        ui->phoneRegister->setPlaceholderText("Phone is EMPTY!");
        halt = true;
    }

    if(ui->lastnameRegister->text() == "")
    {
        ui->lastnameRegister->setPlaceholderText("Last Name EMPTY!");
        halt = true;
    }
    if(!ui->emailRegister->text().contains("@"))
    {
        ui->emailRegister->setText("");
        ui->emailRegister->setPlaceholderText("Enter a valid E-mail!");
        halt = true;
    }


    if(halt)
    {
        ui->regLabel->setText("<b color:#33>Please correct your mistakes.</b>");
    }
    else
    {
        QString username, password, firstnamee, lastname, phone, email, birthdate;
        username = ui->usernameRegister->text();
        password = ui->passwordRegister->text();
        firstnamee = ui->firstnameRegister->text();
        lastname = ui->lastnameRegister->text();
        phone = ui->phoneRegister->text();
        email = ui->emailRegister->text();
        birthdate = ui->birthdateRegister->text();

        if(password.size() < 4)
        {
            ui->passwordRegister->clear();
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
            ui->passwordBox->clear();
        }
        if(ui->passwordRegister_2->text()!= password)
        {
            QMessageBox::warning(this, "Not same", "Passwords are not the same!");
            ui->passwordRegister->clear();
            ui->passwordRegister_2->clear();
        }
        if(!maindatabase::Check_username(username))
        {
            QMessageBox::warning(this,"Duplicate username", "Oh no! We have your username in our database choose another one please!");
            ui->usernameRegister->clear();
        }
        if(!maindatabase::Check_EmailAddress(email))
        {
            QMessageBox::warning(this,"Duplicate email", "Oh no! We have your email in our database choose another one please!");
            ui->emailRegister->clear();
        }
        if(!maindatabase::Check_PhoneNumber(phone))
        {
            QMessageBox::warning(this,"Duplicate phone", "Oh no! We have your phone in our database choose another one please!");
            ui->phoneRegister->clear();
        }

        bool username1, password1, phone1, email1;
        username1 = ui->usernameRegister->text().size();
        password1 = ui->passwordRegister->text().size();
        phone1 = ui->phoneRegister->text().size();
        email1 = ui->emailRegister->text().size();

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


            database->Add_user(userRegister);

            if (this->picName != "")
            {
//                QString to = this->picDir+"/"+ui->usernameRegister->text();

//                if (QFile::exists(to))
//                {
//                    QFile::remove(to);
//                }

//                QFile::copy(this->picName, to);
//                this->picName = "";
                QString path = userRegister.get_UserName() + ".png";
                qDebug() << path;
                qDebug() << userRegister.get_UserName();
                ui->rpLabel->grab().save(path);

            }

            ui->regLabel->setText("");
            ui->usernameRegister->setText("");
            ui->passwordRegister->setText("");
            ui->passwordRegister_2->setText("");
            ui->emailRegister->setText("");
            ui->firstnameRegister->setText("");
            ui->lastnameRegister->setText("");
            ui->phoneRegister->setText("");
            ui->showpassforsignup->setChecked(false);
            ui->rpLabel->setText("<img src=\":/img/img/user.png\" />");
            ui->loginLabel->setText("Registration Successful! You can now login.");
            ui->usernameBox->setText(inneruser.get_UserName());
            ui->passwordBox->setText(inneruser.get_Password());
            ui->winStack->setCurrentIndex(0);
        }
    }
}

void LoginSystem::on_backButton_clicked()
{
    ui->loginLabel->setText("");
    ui->winStack->setCurrentIndex(0);
}

void LoginSystem::on_winStack_currentChanged(int arg1)
{
    if(arg1 == 4 && this->loggedIn)
    {
        ui->winStack->setCurrentIndex(0);
    }
}

void LoginSystem::on_uplButton_clicked()
{
    this->picName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/", tr("Image Files (*.png *.jpg *.bmp)"));
    qDebug() << picName;
    ui->rpLabel->setText("<img src=\"file:///"+this->picName+"\" alt=\"Image read error!\" height=\"128\" width=\"128\" />");

}

void LoginSystem::on_checkBox_showpass_stateChanged(int arg1)
{
    if(arg1)
        ui->passwordBox->setEchoMode(QLineEdit::Normal);
    else
        ui->passwordBox->setEchoMode(QLineEdit::Password);
}

void LoginSystem::on_showpassforsignup_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->passwordRegister->setEchoMode(QLineEdit::Normal);
        ui->passwordRegister_2->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->passwordRegister_2->setEchoMode(QLineEdit::Password);
        ui->passwordRegister->setEchoMode(QLineEdit::Password);
    }
}

void LoginSystem::on_forgetpassbtn_clicked()
{
    ui->winStack->setCurrentIndex(2);
}

void LoginSystem::on_backtologinforgetpass_clicked()
{
    ui->winStack->setCurrentIndex(0);
}


void LoginSystem::on_showpassforforgetpass_clicked()
{
    user forgetpass;
    QString pass, pass1, email, username;
    username = ui->usernameforforgetpass->text();
    email = ui->emailforforgetpass->text();
    forgetpass.set_UserName(username);
    forgetpass.set_EmailAddress(email);
    if(database->userpasswordForforgot(forgetpass, pass))
    {

        pass1 = "Your password is : " + pass;
        ui->statusforforgetpass_4->setText(pass1);
        QPixmap pixmap(":/img/img/icons8-password-64.png"); // Change the picture
        ui->picforgetpass->setPixmap(pixmap);
        ui->usernameBox->setText(username);
        ui->passwordBox->setText(pass);
        delay(2);
        ui->usernameforforgetpass->setText("");
        ui->emailforforgetpass->setText("");
        ui->statusforforgetpass_4->setText("");
        QPixmap pixmap1(":/img/img/icons8-password-window-66.png");
        ui->picforgetpass->setPixmap(pixmap1);
        on_backtologinforgetpass_clicked();
    }
    else
    {
        ui->statusforforgetpass_4->setText("Sorry, User not found");
        delay(2);
    }
    ui->usernameforforgetpass->setText("");
    ui->emailforforgetpass->setText("");
    ui->statusforforgetpass_4->setText("");
}

void LoginSystem::delay(int sec)
{
    QTime dieTime= QTime::currentTime().addSecs(sec);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

