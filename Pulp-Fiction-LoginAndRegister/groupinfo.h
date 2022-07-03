#ifndef GROUPINFO_H
#define GROUPINFO_H

#include <QDialog>
#include <QListWidgetItem>
#include <QWidget>
#include <QCheckBox>
#include "user.h"
#include "customshadoweffect.h"
namespace Ui {
class groupInfo;
}

class groupInfo : public QDialog
{
    Q_OBJECT

public:
    explicit groupInfo(user me ,QVector<user> members , int id , QWidget *parent = nullptr);
    ~groupInfo();
public slots:
    void add_clicked();
    void ok_clicked();
private slots:
    void on_backtohomepage_clicked();

private:
    Ui::groupInfo *ui;
    QVector<QListWidgetItem*> list;
    QVector<user> Groupmembers;
    QVector<QCheckBox*> cheVec;
    QVector<user> selected;

    int idGroup;
    user ME;
};


#endif // GROUPINFO_H
