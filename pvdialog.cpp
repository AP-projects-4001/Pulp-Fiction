#include "pvdialog.h"
#include <QScrollBar>
#include <QHBoxLayout>
pvDialog::pvDialog(int UID ,int FID ,QString name, QVector<QString> messageChannel ,QWidget *parent)
    : QDialog(parent)
{
    myID = UID;
    yourID = FID;

    send = new QPushButton(tr("Send"));
    info = new QPushButton(tr("Info"));

    QByteArray ba = name.toLocal8Bit();
    const char *c_str2 = ba.data();
    setWindowTitle(tr(c_str2));

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

    connect(send, &QPushButton::clicked,
         this, &pvDialog::send_clicked);


}
void pvDialog::send_clicked()
{
    QString mes = sendMessage->text();
    if(!(mes.isEmpty()))
    {
    message->append(mes);
    sendMessage->clear();
    sendMessage->setFocus(Qt::OtherFocusReason);
    }

}
