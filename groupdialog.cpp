#include "groupdialog.h"
#include <QScrollBar>
#include <QHBoxLayout>
groupDialog::groupDialog(int UID , QString groupName , int IDG , QVector<int> memId,QVector<QString> nameMem ,
      QVector<int> ADID,QVector<QString> Admins, QVector<QString> groupMessage ,QWidget *parent)
    : QDialog(parent)
{
    ID = UID;
    IDgroup = IDG;

    QVector<int>::iterator itt;
    for (itt = ADID.begin(); itt != ADID.end(); ++itt) {
         if(ID==*itt)
         {
             isAdmin = true;
             break;
         }
    }
    QVector<int>::iterator ittin;
    for (ittin = memId.begin(); ittin != memId.end(); ++ittin) {
         memberID.push_back(*ittin);
    }

    send = new QPushButton(tr("Send"));
    info = new QPushButton(tr("Info"));

    QVector<QString>::iterator i1;
    for (i1 = nameMem.begin(); i1 != nameMem.end(); ++i1) {
         nameOfmembers.push_back(*i1);
    }

    QVector<QString>::iterator i;
    for (i = Admins.begin(); i != Admins.end(); ++i) {
         nemaOfAdmins.push_back(*i);
    }

    QByteArray ba = groupName.toLocal8Bit();
    const char *c_str2 = ba.data();

    message = new QTextEdit;
    message->setReadOnly(true);
    message->verticalScrollBar()->setSliderPosition(
        message->verticalScrollBar()->maximum());
    sendMessage = new QLineEdit;
    sendMessage->setFocus(Qt::OtherFocusReason);
    vectroToList(groupMessage , message);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(sendMessage);
    layout->addWidget(send);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(message, 1, 0);
    mainLayout->addWidget(info, 0, 0);
    mainLayout->addLayout(layout, 2, 0);
    setLayout(mainLayout);

    setWindowTitle(tr(c_str2));
    connect(send, &QPushButton::clicked,
         this, &groupDialog::send_clicked);
    connect(info, &QPushButton::clicked,
         this, &groupDialog::info_clicked);
}
void groupDialog::send_clicked()
{
    QString mes = sendMessage->text();
    if(!(mes.isEmpty()))
    {
    message->append(mes);
    sendMessage->clear();
    sendMessage->setFocus(Qt::OtherFocusReason);
    }

}

void groupDialog::info_clicked()
{
    ob = new DialogForChannel(true , IDgroup , memberID , nameOfmembers  , nemaOfAdmins, this);
    ob->show();
}
