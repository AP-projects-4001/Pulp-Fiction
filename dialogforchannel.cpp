#include "dialogforchannel.h"
#include <QVBoxLayout>
void vectroToList(QVector<QString> write , QTextEdit* read)
{
    QVector<QString>::iterator itt;
    for (itt = write.begin(); itt != write.end(); ++itt) {
         read->append(*itt);
    }
}
DialogForChannel::DialogForChannel(bool isAdmin,int IDC , QVector<int> memID ,QVector<QString> nameMem ,
                                   QVector<QString> Admin, QWidget *parent )
    : QDialog(parent)
{
    Admins = new QTextEdit;
    Admins->setReadOnly(true);
    members = new QTextEdit;
    members->setReadOnly(true);
    vectroToList(Admin , Admins);
    vectroToList(nameMem , members);
    addAdmin = new QPushButton(tr("Add Admin"));
    membersList = new QListWidget;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(Admins);
    layout->addWidget(members);
    layout->addWidget(addAdmin);
    setLayout(layout);
    this->setFixedSize(200,100);
    if(!isAdmin)
    {
        addAdmin->hide();
    }
}
