#ifndef CONTACTS_H
#define CONTACTS_H

#include <QDialog>
#include "user.h"
#include "maindatabase.h"
#include "customshadoweffect.h"

namespace Ui {
class Contacts;
}

class Contacts : public QDialog
{
    Q_OBJECT

public:
    explicit Contacts(user me ,QWidget *parent = nullptr);
    ~Contacts();

private slots:
    void on_newcontact_clicked();

    void on_searchcontact_textChanged(const QString &arg1);

    void on_backbtn_clicked();

    void on_backtohomepage2_clicked();

private:
    Ui::Contacts *ui;

    user howAmI;
};

#endif // CONTACTS_H
