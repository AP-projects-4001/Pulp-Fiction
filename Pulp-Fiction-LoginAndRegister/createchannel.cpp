#include "createchannel.h"
#include "ui_createchannel.h"

createchannel::createchannel(user me ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createchannel)
{
    ui->setupUi(this);
    howAmI = me;
}

createchannel::~createchannel()
{
    delete ui;
}
