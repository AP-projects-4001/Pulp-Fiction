#ifndef CHANNELINFO_H
#define CHANNELINFO_H

#include <QDialog>
#include <QCheckBox>
#include <QWidget>
#include "user.h"
#include "customshadoweffect.h"
#include <QListWidgetItem>
#include "pvinfo.h"
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

    void on_backtohomepage_clicked();

    void on_adminslistwidget_itemClicked(QListWidgetItem *item);

    void on_addadminbtn_clicked();

    void on_addmemberbtn_clicked();

    void on_memberslistwidget_itemClicked(QListWidgetItem *item);

    void on_completebtn_clicked();

private:
    Ui::channelInfo *ui;

    QVector<QCheckBox*> cheVec;

    QVector<user> Members;
    QVector<user> Admins;
    QVector<user> selected;
    QVector<user> newAdmins;
    QVector<user> selectesList;
    PvInfo* infopv;

    ModeInfo currMode;
    user Me;
    int idChannel;
};

#endif // CHANNELINFO_H
