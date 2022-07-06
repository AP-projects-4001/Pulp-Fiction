#include "graphdialog.h"
#include "ui_graphdialog.h"
#include <QPixmap>
graphdialog::graphdialog( user me, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::graphdialog)
{
    ui->setupUi(this);
    howAmI = me ;
//    QPixmap Guidpic("E:/programing projects/qtmasterbranch/Pulp-Fiction-LoginAndRegister/img/guid.png")  ;
//    int w = ui->guidlable->width() ;
//    int h = ui->guidlable->height() ;
//    ui->guidlable->setPixmap( Guidpic.scaled( w , h , Qt::KeepAspectRatio) ) ;
}

graphdialog::~graphdialog()
{
    delete ui;
}

