#ifndef CHANNELINFO_H
#define CHANNELINFO_H

#include <QDialog>
#include <QCheckBox>
#include <QWidget>
#include "user.h"
namespace Ui {
class channelInfo;
}
enum ModeInfo { AddAdmin , AddMember };
class channelInfo : public QDialog
{
    Q_OBJECT

public:
    explicit channelInfo(user me ,QVector<user> member,QVector<user> admin, int id,QWidget *parent = nullptr);
    ~channelInfo();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::channelInfo *ui;

    QVector<QCheckBox*> cheVec;

    QVector<user> Members;
    QVector<user> Admins;
    QVector<user> selected;
    QVector<user> newAdmins;

    ModeInfo currMode;
    user Me;
    int idChannel;
};

#endif // CHANNELINFO_H
