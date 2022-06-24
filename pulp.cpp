#include "pulp.h"
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QList>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QWidget>
#include <QVBoxLayout>

Pulp::Pulp(QWidget *parent)
    :QWidget(parent)
{
    newChannel = new QPushButton(tr("&create a new channel"));
    newGroup = new QPushButton(tr("&create a new group"));
    setting = new QPushButton(tr("&setting"));
    graph = new QPushButton(tr("&graph"));
    findSomeOne = new QPushButton(tr("&find some one"));

    history = new QListWidget;

    QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(newChannel, Qt::AlignTop);
    buttonLayout1->addWidget(newGroup);
    buttonLayout1->addWidget(setting);
    buttonLayout1->addWidget(graph);
    buttonLayout1->addWidget(findSomeOne);
    buttonLayout1->addStretch();

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(history,0,0);
    mainLayout->addLayout(buttonLayout1, 0,1 );

    convertVectorToList(chats , history);

    setLayout(mainLayout);
}
void Pulp::convertVectorToList(QVector<QString> svec , QListWidget* chatList)
{
    QVector<QString>::iterator itt;
    for (itt = svec.begin(); itt != svec.end(); ++itt) {
         QString s = *itt;
         chatList->addItem(s);
    }

}


