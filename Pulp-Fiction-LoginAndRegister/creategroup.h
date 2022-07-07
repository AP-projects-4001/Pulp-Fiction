#ifndef CREATEGROUP_H
#define CREATEGROUP_H

#include <QDialog>
#include "user.h"
#include <QCheckBox>
#include "customshadoweffect.h"
#include "maindatabase.h"

namespace Ui {
class creategroup;
}

class creategroup : public QDialog
{
    Q_OBJECT

public:
    explicit creategroup(user me ,QWidget *parent = nullptr);
    ~creategroup();
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
    Ui::creategroup *ui;
    user howAmI;
    QString name;

    void setChecks();
};

#endif // CREATEGROUP_H
