#ifndef GRAPHDIALOG_H
#define GRAPHDIALOG_H
#include <QDialog>
#include <QCoreApplication>
#include "user.h"
namespace Ui {
class graphdialog;
}

class graphdialog : public QDialog
{
    Q_OBJECT

public:
    explicit graphdialog( user me ,QWidget *parent = nullptr);
    ~graphdialog();

private slots:


private:
    Ui::graphdialog *ui;
    user howAmI ;
};

#endif // GRAPHDIALOG_H
