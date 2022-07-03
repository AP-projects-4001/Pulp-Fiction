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
    QVector<user> getWrite() const {return write;}
    QVector<QCheckBox*> getCheVec() const {return cheVec;}
    QVector<user> getSelected() const{return selected;}
    int getCount();

private slots:
    void on_submit_clicked();

private:
    Ui::createchannel *ui;
    user howAmI;
    QString name;
    QVector<user> write;
    QVector<QCheckBox*> cheVec;
    QVector<user> selected;
};

#endif // CREATECHANNEL_H
