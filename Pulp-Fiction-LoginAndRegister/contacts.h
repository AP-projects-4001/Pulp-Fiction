#ifndef CONTACTS_H
#define CONTACTS_H

#include <QDialog>
#include "user.h"
#include "maindatabase.h"
#include "customshadoweffect.h"
#include <QListWidgetItem>
#include <QRadioButton>
#include "graph.h"

namespace Ui {
class Contacts;
}

class Contacts : public QDialog
{
    Q_OBJECT

public:
    explicit Contacts(user me ,QWidget *parent = nullptr);
    ~Contacts();
    QString getName () const{return name;}
    QVector<user> write;
    QVector<QCheckBox*> cheVec;
    QVector<QRadioButton*> radVec;
    QVector<user> selected;
    QVector<user> radSelcted;
    QVector<user> myfriends;
    int getCount();

private slots:
    void on_newcontact_clicked();

    void on_searchcontact_textChanged(const QString &arg1);

    void on_backbtn_clicked();

    void on_backtohomepage2_clicked();

    void on_addbtn_clicked();

signals:

    void itemsclicked(QListWidgetItem *item);
private:
    Ui::Contacts *ui;

    user howAmI;
    QString name;

    void showfriendsonlistwidget();
};

#endif // CONTACTS_H
