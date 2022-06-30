#include "dialognewgroup.h"
#include "ui_dialognewgroup.h"

DialogNewGroup::DialogNewGroup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewGroup)
{
    ui->setupUi(this);
}

DialogNewGroup::~DialogNewGroup()
{
    delete ui;
}
