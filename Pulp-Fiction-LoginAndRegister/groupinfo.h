#ifndef GROUPINFO_H
#define GROUPINFO_H

#include <QDialog>
#include <QListWidgetItem>
#include <QWidget>
#include <QCheckBox>
#include "user.h"
#include "customshadoweffect.h"
#include "pvinfo.h"
namespace Ui {
class groupInfo;
}

class groupInfo : public QDialog
{
    Q_OBJECT

public:
    explicit groupInfo(user me ,QVector<user> members , int id , QWidget *parent = nullptr);
    ~groupInfo();

private slots:
    void on_backtohomepage_clicked();

    void on_memberslistwidget_itemClicked(QListWidgetItem *item);

    void on_addmemberbtn_clicked();

    void on_completebtn_clicked();

private:
    Ui::groupInfo *ui;
    QVector<QListWidgetItem*> list;
    QVector<user> Groupmembers;
    QVector<QCheckBox*> cheVec;
    QVector<user> selected;
    QVector<user> selectedList;
    PvInfo * infopv;
    int idGroup;
    user ME;
};


#endif // GROUPINFO_H
