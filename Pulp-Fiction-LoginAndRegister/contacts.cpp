#include "contacts.h"
#include "ui_contacts.h"
#include "QCheckBox"

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

    showfriendsonlistwidget();
}

Contacts::~Contacts()
{
    delete ui;
}

void Contacts::on_newcontact_clicked()
{
    ui->winstack->setCurrentIndex(1);
    write = maindatabase::read_AllUsers();
    ui->alluserslist->setStyleSheet("background-color : rgba(0,0,0,50%); color : black;");
    ui->alluserslist->setFlow(QListView::LeftToRight);
    ui->alluserslist->setGridSize(QSize(200, 30));
    ui->alluserslist->setResizeMode(QListView::Adjust);
    ui->alluserslist->setViewMode(QListView::ListMode);
    ui->alluserslist->setWrapping(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSizeConstraint(QLayout::SetMinimumSize);
    setLayout(layout);
    ui->alluserslist->clear();

    bool isfriend = false;

    QVector<user>::iterator itt;
    for (itt = write.begin(); itt != write.end(); ++itt) {
        if(itt->get_ID() != howAmI.get_ID())
        {
            for(int i = 0; i<howAmI.get_FriendsID().size();i++)
            {
                if(howAmI.get_FriendsID()[i] == itt->get_ID())
                    isfriend = true;
            }
            if(!isfriend)
            {

                auto item = new QListWidgetItem("", ui->alluserslist);
                auto text = new QCheckBox;
                QByteArray ba = (itt->get_UserName()).toLocal8Bit();
                const char *c_str2 = ba.data();
                text->setText(c_str2);
                text->setStyleSheet("QCheckBox { background-color : rgba(0,0,0,0%); color : white; }");
                text->setMinimumSize(100, 20);
                text->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
                layout->addWidget(text);
                selected.push_back(*itt);
                cheVec.push_back(text);
                ui->alluserslist->setItemWidget(item, text);
            }
        }
    }
}


void Contacts::on_searchcontact_textChanged(const QString &arg1)
{
    ui->alluserslist->clear();
    write = maindatabase::read_AllUsers();
    ui->alluserslist->setStyleSheet("background-color : rgba(0,0,0,50%); color : black;");
    ui->alluserslist->setFlow(QListView::LeftToRight);
    ui->alluserslist->setGridSize(QSize(200, 30));
    ui->alluserslist->setResizeMode(QListView::Adjust);
    ui->alluserslist->setViewMode(QListView::ListMode);
    ui->alluserslist->setWrapping(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSizeConstraint(QLayout::SetMinimumSize);
    setLayout(layout);
    ui->alluserslist->clear();

    QVector<user>::iterator itt;
    for (itt = write.begin(); itt != write.end(); ++itt) {
        if((itt->get_UserName().contains(arg1) || itt->get_PhoneNumber().contains(arg1) || itt->get_EmailAddress().contains(arg1) || itt->get_firstname().contains(arg1)) && itt->get_ID() != howAmI.get_ID())
        {
                auto item = new QListWidgetItem("", ui->alluserslist);
                auto text = new QCheckBox;
                QByteArray ba = (itt->get_UserName()).toLocal8Bit();
                const char *c_str2 = ba.data();
                text->setText(c_str2);
                text->setStyleSheet("QCheckBox { background-color : rgba(0,0,0,0%); color : white; }");
                text->setMinimumSize(100, 20);
                text->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
                layout->addWidget(text);
                selected.push_back(*itt);
                cheVec.push_back(text);
                ui->alluserslist->setItemWidget(item, text);
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
    maindatabase::Find_user(howAmI);
    on_backbtn_clicked();
}


void Contacts::on_alluserslist_itemClicked(QListWidgetItem *item)
{
//    maindatabase::Find_user(howAmI);

//    ui->alluserslist->clear();
//    write = maindatabase::read_AllUsers();
//    ui->alluserslist->setStyleSheet("background-color : rgba(0,0,0,50%); color : black;");
//    ui->alluserslist->setFlow(QListView::LeftToRight);
//    ui->alluserslist->setGridSize(QSize(200, 30));
//    ui->alluserslist->setResizeMode(QListView::Adjust);
//    ui->alluserslist->setViewMode(QListView::ListMode);
//    ui->alluserslist->setWrapping(true);
//    QVBoxLayout *layout = new QVBoxLayout;
//    layout->setSizeConstraint(QLayout::SetMinimumSize);
//    setLayout(layout);
//    ui->alluserslist->clear();

//    QVector<user>::iterator itt;
//    for (itt = write.begin(); itt != write.end(); ++itt) {
//        if((itt->get_UserName().contains(arg1) || itt->get_PhoneNumber().contains(arg1) || itt->get_EmailAddress().contains(arg1) || itt->get_firstname().contains(arg1)) && itt->get_ID() != howAmI.get_ID())
//        {
//            auto item = new QListWidgetItem("", ui->alluserslist);
//            auto text = new QCheckBox;
//            QByteArray ba = (itt->get_UserName()).toLocal8Bit();
//            const char *c_str2 = ba.data();
//            text->setText(c_str2);
//            text->setStyleSheet("QCheckBox { background-color : rgba(0,0,0,0%); color : white; }");
//            text->setMinimumSize(100, 20);
//            text->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
//            layout->addWidget(text);
//            selected.push_back(*itt);
//            cheVec.push_back(text);
//            ui->alluserslist->setItemWidget(item, text);
//        }
//    }
}

void Contacts::showfriendsonlistwidget()
{
    qDebug() << "In show on list widget";
    maindatabase::Find_user(howAmI);
    ui->freindslist->clear();
    ui->freindslist->setStyleSheet("background-color : rgba(0,0,0,50%); color : black;");
    ui->freindslist->setFlow(QListView::LeftToRight);
    ui->freindslist->setGridSize(QSize(200, 30));
    ui->freindslist->setResizeMode(QListView::Adjust);
    ui->freindslist->setViewMode(QListView::ListMode);
    ui->freindslist->setWrapping(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSizeConstraint(QLayout::SetMinimumSize);
    setLayout(layout);


    QVector<int> friendsids = howAmI.get_FriendsID();
    QVector<user> myfriends;
    for(int i = 0; i < friendsids.size(); i++)
    {
        myfriends.push_back(maindatabase::getUserdetails(friendsids[i]));
    }


    for (int i = 0; i < myfriends.size(); i++) {
        qDebug() << "In add Qradiobutton on list widget";
        auto item = new QListWidgetItem("", ui->freindslist);
        auto text = new QRadioButton;
        QByteArray ba = (myfriends[i].get_UserName()).toLocal8Bit();
        qDebug() << "In friends know on list widget";
        qDebug() << myfriends[i].get_UserName();
        const char *c_str2 = ba.data();
        text->setText(c_str2);
        text->setStyleSheet("QRadioButton { background-color : rgba(0,0,0,0%); color : white; padding-left:10px; padding-top:5px;}");
        text->setMinimumSize(100, 20);
        text->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        layout->addWidget(text);
        selected.push_back(myfriends[i]);
        radVec.push_back(text);
        ui->freindslist->setItemWidget(item, text);
    }
}


void Contacts::on_startchat_clicked()
{
    for (int i = 0; i< radVec.size(); i++) {
        if(radVec[i]->isChecked())
        {
//             maindatabase::Push_UserFriendID(selected[i].get_ID(), howAmI);
        }
    }
}

