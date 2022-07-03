#ifndef CREATECHANNEL_H
#define CREATECHANNEL_H

#include <QDialog>
#include "user.h"
#include <QCheckBox>

namespace Ui {
class createchannel;
}

class createchannel : public QDialog
{
    Q_OBJECT

public:
    explicit createchannel(user me ,QWidget *parent = nullptr);
    ~createchannel();
    QString getName () const{return name;}
    QVector<user> write;
    QVector<QCheckBox*> cheVec;
    QVector<user> selected;
    int getCount();

private slots:
    void on_submit_clicked();

    void on_backbtn_5_clicked();

    void on_backbtn_3_clicked();

private:
    Ui::createchannel *ui;
    user howAmI;
    QString name;

};

#endif // CREATECHANNEL_H
