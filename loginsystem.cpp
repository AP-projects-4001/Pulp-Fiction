#include "loginsystem.h"
#include "ui_loginsystem.h"
//#include "qdb.h"
#include <QSqlRecord>
#include <QFileDialog>
#include <QMessageBox>
#include <QDate>

//QDBLite::DB db;

LoginSystem::LoginSystem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginSystem)
{
    ui->setupUi(this);
    database = new maindatabase();
//    db.dbstate = db.Connect("C:\\Users\\tejarat pooya\\Pictures\\Desktop\\AP project\\Login-System\\database\\users_login_register.db");
    ui->winStack->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(1);

    ui->passwordBox->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    ui->passwordRegister->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    ui->pBox_2->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
}

LoginSystem::~LoginSystem()
{
    delete ui;
}

void LoginSystem::on_loginButton_clicked()
{
//    this->loggedIn = Login(ui->usernameBox->text(), ui->passwordBox->text());

//    if(this->loggedIn)
//    {
//        this->username = ui->usernameBox->text();
//        this->password = ui->passwordBox->text();

//        ui->loginLabel->setText("");
//        ui->winStack->setCurrentIndex(2);
//    }
//    else
//    {
//        ui->loginLabel->setText("Login failed: Invalid credentials!");
//    }
}

bool LoginSystem::Login(QString u, QString p)
{

//    ui->adminButton->setVisible(false);

//    bool exists = false;

//    QSqlQuery checkQuery(db.db);
//    checkQuery.prepare("select * from users where username='"+u+"' and password='"+p+"'");

//    if (checkQuery.exec())
//    {
//        if (checkQuery.next())
//        {
//            exists = true;
//        }
//    }

//    return exists;
}


void LoginSystem::on_regButton_clicked()
{
    ui->usernameRegister->setText(ui->usernameBox->text());
    ui->passwordRegister->setText(ui->passwordBox->text());
    ui->winStack->setCurrentIndex(1);
}

void LoginSystem::on_logoutButton_clicked()
{
//    if(QMessageBox::Yes == QMessageBox(QMessageBox::Question,
//                                       "Login System", "Are you sure you want to logout?",
//                                       QMessageBox::Yes|QMessageBox::No).exec())
//    {
//        this->loggedIn = false;
//        ui->passwordBox->setText("");
//        ui->loginLabel->setText("You signed out!");
//        ui->winStack->setCurrentIndex(0);
//    }
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


    if(halt)
    {
        ui->regLabel->setText("Please correct your mistakes.");
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
            ui->emailRegister->clear();
        }
        bool username1, password1, phone1, email1;
        username1 = ui->usernameRegister->text().size();
        password1 = ui->passwordRegister->text().size();
        phone1 = ui->phoneRegister->text().size();
        email1 = ui->emailRegister->text().size();

        if(username1 && password1 && phone1 && email1)
        {
            inneruser.set_ID(maindatabase::Creat_ID());
            inneruser.set_UserName(username);
            inneruser.set_Password(password);
            inneruser.set_EmailAddress(email);
            inneruser.set_Firstname(firstnamee);
            inneruser.set_Lastname(lastname);
            inneruser.set_BirthDate(birthdate);
            inneruser.set_PhoneNumber(phone);

            database->Add_user(inneruser);
//            if (this->picName != "")
//            {
//                QString to = this->picDir+"/"+ui->usernameRegister->text();

//                if (QFile::exists(to))
//                {
//                    QFile::remove(to);
//                }

//                QFile::copy(this->picName, to);
//                this->picName = "";
//            }

            ui->regLabel->setText("");
            ui->usernameRegister->setText("");
            ui->passwordRegister->setText("");
            ui->emailRegister->setText("");
            ui->firstnameRegister->setText("");
            ui->lastnameRegister->setText("");
            ui->rpLabel->setText("<img src=\":/img/img/user.png\" />");
            ui->loginLabel->setText("Registration Successful! You can now login.");
            ui->winStack->setCurrentIndex(0);
        }
    }
}

void LoginSystem::on_backButton_clicked()
{
    ui->loginLabel->setText("");
    ui->winStack->setCurrentIndex(0);
}


void LoginSystem::on_backButton_2_clicked()
{
    ui->winStack->setCurrentIndex(2);
}


void LoginSystem::on_editButton_clicked()
{
//    QSqlQuery fetcher;
//    fetcher.prepare("SELECT * FROM users WHERE username = (:un) AND passwd = (:pw)");
//    fetcher.bindValue(":un", this->username);
//    fetcher.bindValue(":pw", this->password);
//    fetcher.exec();

//    int idUsername = fetcher.record().indexOf("username");
//    int idPasswd = fetcher.record().indexOf("passwd");
//    int idEmail = fetcher.record().indexOf("email");
//    int idFname = fetcher.record().indexOf("fname");
//    int idMname = fetcher.record().indexOf("mname");
//    int idLname = fetcher.record().indexOf("lname");

//    while (fetcher.next())
//    {
//        ui->uBox_2->setText(fetcher.value(idUsername).toString());
//        ui->pBox_2->setText(fetcher.value(idPasswd).toString());
//        ui->eBox_2->setText(fetcher.value(idEmail).toString());
//        ui->fBox_2->setText(fetcher.value(idFname).toString());
//        ui->mBox_2->setText(fetcher.value(idMname).toString());
//        ui->lBox_2->setText(fetcher.value(idLname).toString());
//    }

    ui->winStack->setCurrentIndex(3);
}

void LoginSystem::on_delButton_clicked()
{
//    if(QMessageBox::Yes == QMessageBox(QMessageBox::Question,
//                                       "Login System", "Are you sure you want to delete your account?",
//                                       QMessageBox::Yes|QMessageBox::No).exec())
//    {
//        QString to = this->picDir+"/"+this->username;

//        if (QFile::exists(to))
//        {
//            QFile::remove(to);
//        }

//        QSqlQuery dQuery(db.db);
//        dQuery.prepare("DELETE FROM users WHERE username = (:un)");
//        dQuery.bindValue(":un", this->username);

//        if(dQuery.exec())
//        {
//            ui->usernameBox->setText("");
//            ui->passwordBox->setText("");
//            ui->loginLabel->setText("Account deleted!");
//            ui->winStack->setCurrentIndex(0);
//        }
//    }
}

void LoginSystem::on_editedButton_clicked()
{


//    bool halt = false;

//    if(ui->uBox_2->text() == "")
//    {
//        ui->uBox_2->setPlaceholderText("Username EMPTY!");
//        halt = true;
//    }

//    if(ui->pBox_2->text() == "")
//    {
//        ui->pBox_2->setPlaceholderText("Password EMPTY!");
//        halt = true;
//    }

//    if(ui->eBox_2->text() == "")
//    {
//        ui->eBox_2->setPlaceholderText("E-mail EMPTY!");
//        halt = true;
//    }

//    if(ui->fBox_2->text() == "")
//    {
//        ui->fBox_2->setPlaceholderText("First Name EMPTY!");
//        halt = true;
//    }

//    if(ui->mBox_2->text() == "")
//    {
//        ui->mBox_2->setPlaceholderText("Middle Name (optional)");
//        halt = false;
//    }

//    if(ui->lBox_2->text() == "")
//    {
//        ui->lBox_2->setPlaceholderText("Last Name EMPTY!");
//        halt = true;
//    }

//    QSqlQuery cQuery(db.db);
//    cQuery.prepare("SELECT username FROM users WHERE username = (:un)");
//    cQuery.bindValue(":un", ui->uBox->text());

//    if(cQuery.exec())
//    {
//        if(cQuery.next() && ui->uBox_2->text() != cQuery.value(0).toString())
//        {
//            ui->uBox_2->setText("");
//            ui->uBox_2->setPlaceholderText("Choose a different Username!");
//            halt = true;
//        }
//    }

//    QSqlQuery cQuery2(db.db);
//    cQuery2.prepare("SELECT email FROM users WHERE email = (:em)");
//    cQuery2.bindValue(":em", ui->eBox_2->text());

//    if(cQuery2.exec())
//    {
//        if(cQuery2.next() && ui->eBox_2->text() != cQuery2.value(0).toString())
//        {
//            ui->eBox_2->setText("");
//            ui->eBox_2->setPlaceholderText("Use another E-mail!");
//            halt = true;
//        }
//    }

//    if(halt)
//    {
//        ui->regLabel_2->setText("Please correct your mistakes.");
//    }
//    else
//    {
//        if (this->picName != "")
//        {
//            QString to = this->picDir+"/"+ui->uBox_2->text();

//            if (QFile::exists(to))
//            {
//                QFile::remove(to);
//            }

//            QFile::copy(this->picName, to);
//            this->picName = "";
//        }

//        ui->regLabel_2->setText("");
//        QSqlQuery iQuery(db.db);
//        iQuery.prepare("UPDATE users SET username=(:un), passwd=(:pw), fname=(:fn), mname=(:mn), lname=(:ln), email=(:em) WHERE username=(:uno)");
//        iQuery.bindValue(":un", ui->uBox_2->text());
//        iQuery.bindValue(":pw", ui->pBox_2->text());
//        iQuery.bindValue(":fn", ui->fBox_2->text());
//        iQuery.bindValue(":mn", ui->mBox_2->text());
//        iQuery.bindValue(":ln", ui->lBox_2->text());
//        iQuery.bindValue(":em", ui->eBox_2->text());
//        iQuery.bindValue(":uno", ui->uBox_2->text());

//        if(iQuery.exec())
//        {
//            ui->winStack->setCurrentIndex(2);
//        }

//    }
}

void LoginSystem::on_winStack_currentChanged(int arg1)
{

    if(arg1 == 3 && this->loggedIn)
    {
        if(QFile::exists(this->picDir+"/"+this->username))
        {
            ui->rpLabel_2->setText("<img src=\"file:///"+this->picDir+"/"+this->username+"\" alt=\"Image read error!\" height=\"128\" width=\"128\" />");
        }
    }

    if(arg1 == 2 && this->loggedIn)
    {
        if(QFile::exists(this->picDir+"/"+this->username))
        {
            ui->loggedPic->setText("<img src=\"file:///"+this->picDir+"/"+this->username+"\" alt=\"Image read error!\" height=\"128\" width=\"128\" />");
        }

//        QSqlQuery fetcher;
//        fetcher.prepare("SELECT * FROM users WHERE username = (:un)");
//        fetcher.bindValue(":un", this->username);
//        fetcher.exec();

//        int idFname = fetcher.record().indexOf("fname");
//        int idMname = fetcher.record().indexOf("mname");
//        int idLname = fetcher.record().indexOf("lname");
//        int idRank = fetcher.record().indexOf("rank");
//        int idEmail = fetcher.record().indexOf("email");

//        QString fullname, email, rank;

//        while (fetcher.next())
//        {
//            fullname = fetcher.value(idFname).toString();
//            fullname += " " + fetcher.value(idMname).toString();
//            fullname += " " + fetcher.value(idLname).toString();
//            rank = fetcher.value(idRank).toString();
//            email = fetcher.value(idEmail).toString();
//        }
//        if(rank == "-1")
//        {
//            ui->adminButton->setVisible(true);
//        }
//        ui->nameLabel->setText(fullname);
//        ui->rankLabel->setText(rank);
//        ui->emailLabel->setText(email);
    }

    if(arg1 == 4 && this->loggedIn)
    {
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void LoginSystem::on_uplButton_clicked()
{
    this->picName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/", tr("Image Files (*.png *.jpg *.bmp)"));
    ui->rpLabel->setText("<img src=\"file:///"+this->picName+"\" alt=\"Image read error!\" height=\"128\" width=\"128\" />");

}

void LoginSystem::on_uplButton_2_clicked()
{
    this->picName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/", tr("Image Files (*.png *.jpg *.bmp)"));
    ui->rpLabel_2->setText("<img src=\"file:///"+this->picName+"\" alt=\"Image read error!\" height=\"128\" width=\"128\" />");
}

void LoginSystem::on_adminButton_clicked()
{
    ui->winStack->setCurrentIndex(4);
}

void LoginSystem::on_pageButton_clicked()
{
    ui->winStack->setCurrentIndex(2);
}

void LoginSystem::on_editedButton_2_clicked()
{
//    if(this->tblMdl->submitAll())
//    {
//        this->tblMdl->database().commit();
//        ui->adminLabel->setText("Saved to database!");
//    }
//    else
//    {
//        this->tblMdl->database().rollback();
//    }
}

void LoginSystem::on_backButton_5_clicked()
{
//    this->tblMdl->revertAll();
//    this->tblMdl->database().rollback();
}

void LoginSystem::on_userBrowse_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void LoginSystem::on_delUButton_clicked()
{
//    if(QMessageBox::Yes == QMessageBox(QMessageBox::Question,
//                                           "Login System", "Are you sure you want to erase all accounts?",
//                                           QMessageBox::Yes|QMessageBox::No).exec())
//    {
//        QSqlQuery dQuery(db.db);
//        dQuery.prepare("DELETE FROM users WHERE rank != 0 AND rank != -1");

//        if(dQuery.exec())
//        {
//            ui->adminLabel->setText("Query executed!");
//        }
//    }
}

void LoginSystem::on_stackedWidget_currentChanged(int arg1)
{
//    if(arg1 == 0 && this->loggedIn)
//    {
//        ui->headLabel->setText("USERS");
//        this->tblMdl = new QSqlTableModel;
//        this->tblMdl->setTable("users");
//        this->tblMdl->setFilter("rank != -1 AND rank != 0");
//        this->tblMdl->select();
//        ui->tableView->setModel(this->tblMdl);
//        this->tblMdl->database().transaction();
//    }

//    if(arg1 == 1 && this->loggedIn)
//    {
//        ui->headLabel->setText("ADMINS");
//        this->tblMdl = new QSqlTableModel;
//        this->tblMdl->setTable("users");
//        this->tblMdl->setFilter("rank == -1 OR rank == 0");
//        this->tblMdl->select();
//        ui->tableView_2->setModel(this->tblMdl);
//        this->tblMdl->database().transaction();
//    }
}

void LoginSystem::on_adminBrowse_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void LoginSystem::on_delAButton_clicked()
{
//    if(QMessageBox::Yes == QMessageBox(QMessageBox::Question,
//                                           "Login System", "Are you sure you want to erase all administrators?"\
//                                           "\n(This won't erase regular users and you)",
//                                           QMessageBox::Yes|QMessageBox::No).exec())
//    {
//        QSqlQuery dQuery(db.db);
//        dQuery.prepare("DELETE FROM users WHERE rank != 1 AND username != \"" + this->username + "\"");

//        if(dQuery.exec())
//        {
//            ui->adminLabel->setText("Query executed!");
//        }
//    }
}

void LoginSystem::on_checkBox_showpass_stateChanged(int arg1)
{
    if(arg1)
        ui->passwordBox->setEchoMode(QLineEdit::Normal);
    else
        ui->passwordBox->setEchoMode(QLineEdit::Password);
}


void LoginSystem::on_checkBox_stateChanged(int arg1)
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

