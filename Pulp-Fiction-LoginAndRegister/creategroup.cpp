#include "creategroup.h"
#include "ui_creategroup.h"

creategroup::creategroup(user me ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::creategroup)
{
    ui->setupUi(this);
    howAmI = me;
    ui->winstack->setCurrentIndex(0);
    ui->groupname->clear();
    // Sets UI and shadow for it
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(20.0);
    bodyShadow->setDistance(4.0);
    bodyShadow->setColor(QColor(10, 5, 45, 80));
    ui->winstack->setGraphicsEffect(bodyShadow);

    write = maindatabase::read_AllUsers();
    ui->userslist->setStyleSheet("background-color : rgba(0,0,0,50%); color : black;");
    ui->userslist->setFlow(QListView::LeftToRight);
    ui->userslist->setGridSize(QSize(200, 30));
    ui->userslist->setResizeMode(QListView::Adjust);
    ui->userslist->setViewMode(QListView::ListMode);
    ui->userslist->setWrapping(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSizeConstraint(QLayout::SetMinimumSize);
    setLayout(layout);
    ui->userslist->clear();

    QVector<user>::iterator itt;
    for (itt = write.begin(); itt != write.end(); ++itt) {
        if(itt->get_ID() != me.get_ID())
        {
            auto item = new QListWidgetItem("", ui->userslist);
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
            ui->userslist->setItemWidget(item, text);
        }
    }
    connect(ui->addbtn, &QPushButton::clicked,
            this, &creategroup::accept);
}

creategroup::~creategroup()
{
    delete ui;
}

void creategroup::on_submit_clicked()
{
    name = ui->groupname->text();
    ui->winstack->setCurrentIndex(1);
}
int creategroup::getCount()
{return ui->userslist->count();}

void creategroup::on_backbtn_5_clicked()
{
    ui->groupname->clear();
    ui->winstack->setCurrentIndex(0);
}
void creategroup::on_backbtn_3_clicked()
{
    creategroup::hide();
}
