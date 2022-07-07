#include "graphdialog.h"
#include "ui_graphdialog.h"
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>
graphdialog::graphdialog( user me, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::graphdialog)
{
    ui->setupUi(this);
    howAmI = me ;
}

graphdialog::~graphdialog()
{
    delete ui;
}


void graphdialog::on_pushButton_clicked()
{
    QString link =  "https://www.google.com";
    QDesktopServices::openUrl(QUrl(link));
}

