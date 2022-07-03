#include "newgroup.h"
#include "ui_newgroup.h"
#include <QVBoxLayout>
#include <QCheckBox>
#include "maindatabase.h"
#include <QMessageBox>
newGroup::newGroup(user who,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newGroup)
{
    howAmI = who;
    ui->setupUi(this);
    ui->listWidget->hide();
    ui->pushButton->hide();
    write = maindatabase::read_AllUsers();
    for(int i = 0 ; i < write.count() ; i++)
    qDebug() << write[i].get_UserName();
    ui->listWidget->setStyleSheet("background-color : rgba(0,0,0,50%); color : black;");
    ui->listWidget->setFlow(QListView::LeftToRight);
    ui->listWidget->setGridSize(QSize(200, 30));
    ui->listWidget->setResizeMode(QListView::Adjust);
    ui->listWidget->setViewMode(QListView::ListMode);
    ui->listWidget->setWrapping(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSizeConstraint(QLayout::SetMinimumSize);
    setLayout(layout);
    ui->listWidget->clear();

    QVector<user>::iterator itt;
    for (itt = write.begin(); itt != write.end(); ++itt) {
        if(itt->get_ID() != who.get_ID())
        {
            auto item = new QListWidgetItem("", ui->listWidget);
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
            ui->listWidget->setItemWidget(item, text);
        }
    }
    connect(ui->pushButton, &QPushButton::clicked,
            this, &newGroup::accept);


}

newGroup::~newGroup()
{
    delete ui;
}

int newGroup::getCount()const
{
    return ui->listWidget->count();
}


void newGroup::on_pushButton_2_clicked()
{
    name = ui->lineEdit->text();
    if(name.isEmpty())
        QMessageBox::information(this, tr("ENTER NAME"),
            tr("Please enter a name"));
}

