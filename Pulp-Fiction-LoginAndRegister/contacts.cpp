#include "contacts.h"
#include "ui_contacts.h"
#include "QCheckBox"
#include "countlessCalledFunctions.h"
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

    connect(ui->startchat, &QPushButton::clicked,
            this, &Contacts::accept);
    showfriendsonlistwidget();
}

Contacts::~Contacts()
{
    delete ui;
}

int Contacts::getCount()
{
    return ui->freindslist->count();
}

void Contacts::on_newcontact_clicked()
{
    selected.clear();
    cheVec.clear();
    write.clear();
    ui->winstack->setCurrentIndex(1);
    write = maindatabase::read_AllUsers();
    ui->alluserslist->setStyleSheet("background-color : rgba(0,0,0,50%); color : black;");

   QVBoxLayout* layout = setQwidgetItemsInListWidget(ui->alluserslist , 200 , 30);

    ui->alluserslist->clear();


    QVector<user>::iterator itt;
    for (itt = write.begin(); itt != write.end(); ++itt) {
        bool isfriend = false;
        if(itt->get_ID() != howAmI.get_ID())
        {
            for(int i = 0; i<howAmI.get_FriendsID().size();i++)
            {
                if(howAmI.get_FriendsID()[i] == itt->get_ID())
                {
                    isfriend = true;
                    break;
                }
            }
            if(!isfriend)
            {

                QCheckBox* text = writeCheckBox(ui->alluserslist ,layout , itt->get_UserName());
                text->setStyleSheet("QCheckBox { background-color : rgba(0,0,0,0%); color : white; }");
                selected.push_back(*itt);
                cheVec.push_back(text);
            }
        }
    }
}


void Contacts::on_searchcontact_textChanged(const QString &arg1)
{
    selected.clear();
    cheVec.clear();
    write.clear();
    ui->alluserslist->clear();
    if(arg1 == "")
    {
        on_newcontact_clicked();
        return;
    }
    write = maindatabase::read_AllUsers();
    ui->alluserslist->setStyleSheet("background-color : rgba(0,0,0,50%); color : black;");
    QVBoxLayout* layout = setQwidgetItemsInListWidget(ui->alluserslist , 200 , 30);
    ui->alluserslist->clear();

    QVector<user>::iterator itt;
    for (itt = write.begin(); itt != write.end(); ++itt)
    {
        bool isfriend = false;
        if(itt->get_ID() != howAmI.get_ID())
        {
            for(int i = 0; i<howAmI.get_FriendsID().size();i++)
            {
                if(howAmI.get_FriendsID()[i] == itt->get_ID())
                {
                    isfriend = true;
                    break;
                }
            }
            if(!isfriend && (itt->get_UserName().contains(arg1) || itt->get_EmailAddress().contains(arg1) || itt->get_PhoneNumber().contains(arg1)))
            {

                QCheckBox* text = writeCheckBox(ui->alluserslist ,layout , itt->get_UserName());
                text->setStyleSheet("QCheckBox { background-color : rgba(0,0,0,0%); color : white; }");
                selected.push_back(*itt);
                cheVec.push_back(text);
            }
        }
    }
}

void Contacts::on_backbtn_clicked()
{
    ui->winstack->setCurrentIndex(0);
    showfriendsonlistwidget();
}

void Contacts::on_backtohomepage2_clicked()
{
    Contacts::hide();
}


void Contacts::on_addbtn_clicked()
{
    for (int i = 0; i< cheVec.size(); i++) {
        if(cheVec[i]->isChecked())
        {
             maindatabase::Push_UserFriendID(selected[i].get_ID(), howAmI);
        }
    }
    on_backbtn_clicked();
}


void Contacts::showfriendsonlistwidget()
{
    maindatabase::Find_user(howAmI);
    QVBoxLayout* layout = setQwidgetItemsInListWidget(ui->freindslist , 200 , 30);
    ui->freindslist->clear();
    ui->freindslist->setStyleSheet("background-color : rgba(0,0,0,50%); color : black;");

    QVector<int> friendsids = howAmI.get_FriendsID();
    myfriends.clear();
    radVec.clear();
    qDebug() << "new one";
    for(int i = 0; i < friendsids.size(); i++)
    {
        myfriends.push_back(maindatabase::getUserdetails(friendsids[i]));
        qDebug() << myfriends[i].get_UserName();
        QRadioButton* text = writeRAdioButton(ui->freindslist , layout , myfriends[i].get_UserName());
        radVec.push_back(text);
    }

}

