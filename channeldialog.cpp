#include "channeldialog.h"
#include <QPushButton>
#include <QTextEdit>
#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QScrollBar>
channelDialog::channelDialog(int UID,QString nameChannel, int IDC , QVector<int> memId ,
QVector<QString> nameMem,QVector<int> ADID ,QVector<QString> Admins, QVector<QString> messageChannel ,QWidget *parent)
: QDialog(parent)
{
    ID = UID;
    IDchannel = IDC;

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

    QByteArray ba = nameChannel.toLocal8Bit();
    const char *c_str2 = ba.data();

    message = new QTextEdit;
    message->setReadOnly(true);
    message->verticalScrollBar()->setSliderPosition(
        message->verticalScrollBar()->maximum());
    sendMessage = new QLineEdit;
    sendMessage->setFocus(Qt::OtherFocusReason);
    vectroToList(messageChannel , message);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(sendMessage);
    layout->addWidget(send);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(message, 1, 0);
    mainLayout->addWidget(info, 0, 0);
    mainLayout->addLayout(layout, 2, 0);
    setLayout(mainLayout);

    setWindowTitle(tr(c_str2));
    if(!isAdmin)
    {
        info->hide();
        send->hide();
        sendMessage->hide();
    }

    connect(send, &QPushButton::clicked,
         this, &channelDialog::send_clicked);
    connect(info, &QPushButton::clicked,
         this, &channelDialog::info_clicked);

}

void channelDialog::send_clicked()
{
    QString mes = sendMessage->text();
    if(!(mes.isEmpty()))
    {
    message->append(mes);
    sendMessage->clear();
    sendMessage->setFocus(Qt::OtherFocusReason);
    }

}

void channelDialog::info_clicked()
{
    ob = new DialogForChannel(true , IDchannel , memberID , nameOfmembers  , nemaOfAdmins, this);
    ob->show();
}
